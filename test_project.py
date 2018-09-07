import os
import sys
import signal
import subprocess
import time

def start_app_and_wait(conf, requests):
	if os.path.isfile('err'):
		os.remove('err')
	proc = subprocess.Popen('./intern_project ' + conf + ' ' + requests + ' log &> err', shell=True,preexec_fn=os.setsid)
	while (True):
		if (os.path.isfile('err')):
			st = os.stat('err');
			if st.st_size > 0:
				break

	os.killpg(proc.pid, signal.SIGINT)



def testRequestsPerAgent(content, agents, tracks):

	good = True
	max_time = int(content[-3].split(":")[0])
	agents_time = []
	tracks_time = []
	for agent in agents:	
		agents_time.append((agent,zip(range(0,max_time + 1),[0] * (max_time + 1))))


	for track in tracks:
		tracks_time.append((track,[0] * (max_time + 1)))

	requests = {} 

	for line in content:
		if "RECEIVE" in line:
			time = int(line[0:4])
			req_id = int(line.split("---")[1].split(":")[1])
			agent_id = int(line.split("---")[2].split(":")[1])
			track_id = int(line.split("---")[3].split(":")[1].strip("\n"))
			process_time = int(line.split("---")[4].split(":")[1].strip("\n"))
			requests[req_id] = (time,agent_id, track_id, process_time)
		if "SUCCESS" in line:
			time = int(line[0:4])
			req_id = int(line.split("---")[1].split(":")[1])
			requests[req_id] = requests[req_id] + (time,)

	for req_id in requests:
		val = requests[req_id]
		time = val[0]
		agent = val[1]
		track = val[2]
		process_time = val[3]
		finish_time = val[4]
		for i in range(time,finish_time):
			agents_time[agent - 1][1][i] = (i,agents_time[agent - 1][1][i][1] + 1)
		for i in range(process_time,finish_time):
			tracks_time[track - 1][1][i] = tracks_time[track - 1][1][i] + 1 


	for agent in agents_time:
		cap = agents[agent[0]][1]
		for (tmp,loading) in agent[1]:
			good = good and (loading <= cap)
			good = good and (loading >= 0)

	for track in tracks_time:
		for time in track[1]:
			good = good and (time < 2)
			good = good and (time >= 0)
	return good

def testSecventialLog(content, agents, tracks):
	failed = 0
	success = 0
	receive = 0
	good = True

	for line in content:
		if "RECEIVE REQUEST" in line:
			receive = receive + 1
		elif "FAILED REQUEST" in line or "UNSUPPORTED REQUEST" in line:
			failed = failed + 1
		elif "SUCCESS REQUEST" in line:
			success = success + 1

	good = good and (failed == 0)
	good = good and (success == 10)
	good = good and (receive == 10)
	good = good and testRequestsPerAgent(content,agents,tracks)
	return good


def testParalelLog(content, agents, tracks):
	failed = 0
	success = 0
	receive = 0
	good = True

	for line in content:
		if "RECEIVE REQUEST" in line:
			receive = receive + 1
		elif "FAILED REQUEST" in line or "UNSUPPORTED REQUEST" in line:
			failed = failed + 1
		elif "SUCCESS REQUEST" in line:
			success = success + 1

	good = good and (failed == 0)
	good = good and (success == 18)
	good = good and (receive == 18)
	good = good and testRequestsPerAgent(content,agents,tracks)
	return good

def testFailedLog(content, agents, tracks):
	failed = 0
	success = 0
	receive = 0
	good = True

	for line in content:
		if "RECEIVE REQUEST" in line:
			receive = receive + 1
		elif "FAILED REQUEST" in line or "UNSUPPORTED REQUEST" in line:
			failed = failed + 1
		elif "SUCCESS REQUEST" in line:
			success = success + 1

	good = good and (failed == 6)
	good = good and (success == 6)
	good = good and (receive == 6)
	return good

def run_test(callback):

	content = None
	with open('airport.log', "r") as f:
		content = f.readlines()

	content = [x.strip() for x in content]
	index_agents = content.index("Agents:")
	index_tracks = content.index("Tracks:")
	agents = {}
	tracks = {}

	for i in range(index_agents + 1, index_tracks - 1):
		id = content[i].split("---")[0].split("[")[1].strip("]")
		name = content[i].split("---")[1].split("[")[1].strip("]")
		capacity = content[i].split("--")[2].split("[")[1].strip("]")
		agents[id] = (name,capacity)

	for i in range(index_tracks + 1, len(content)):
		id = content[i].split("---")[0].split("[")[1].strip("]")
		size = content[i].split("---")[1].split("[")[1].strip("]")
		type = content[i].split("---")[2].split("[")[1].strip("]")
		tracks[id] = (size,type)


	with open('log', 'r') as f:
		content = f.readlines()
	return callback(content,agents,tracks)

def test_file_not_found(conf, requests):
	start_time = time.time()
	start_app_and_wait(conf,requests)
	with open('err') as f:
		content = f.read().strip('\n')
	validity = content == 'Exception raised: File does not exist'
	if validity:
		result = 'PASS'
	else:
		result = 'FAIL'
	
	total = round(time.time() - start_time,4)
	os.remove('./err')
	print('Time[' + str(total) + '] - Test file not found - ' + result)

def test_conf_not_good(conf, requests):
	start_time = time.time()
	start_app_and_wait(conf,requests)
	with open('err') as f:
		content = f.read().strip('\n')

	validity = 'Bad conf' in content
	
	if validity:
		result = 'PASS'
	else:
		result = 'FAIL'
	total = round(time.time() - start_time,4)
	os.remove('./err')
	print('Time[' + str(total) + '] - Test conf not good - ' + result)

def test_sequential(conf, requests):
	start_time = time.time()
	start_app_and_wait(conf,requests)
	good = run_test(testSecventialLog)
	if good:
		result = 'PASS'
	else:
		result = 'FAIL'

	total = round(time.time() - start_time,4)
	os.remove('./err')
	print('Time[' + str(total) + '] - Test sequential - ' + result)

def test_paralel(conf, requests):
	start_time = time.time()
	start_app_and_wait(conf,requests)
	good = run_test(testParalelLog)
	if good:
		result = 'PASS'
	else:
		result = 'FAIL'
	total = round(time.time() - start_time,4)
	os.remove('./err')
	print('Time[' + str(total) + '] - Test paralel - ' + result)

def test_failed(conf, requests):
	start_time = time.time()
	start_app_and_wait(conf,requests)
	good = run_test(testFailedLog)
	if good:
		result = 'PASS'
	else:
		result = 'FAIL'
	total = round(time.time() - start_time,4)
	os.remove('./err')
	print('Time[' + str(total) + '] - Test failed - ' + result)


tests = [
	(0,'Test file not found',test_file_not_found, 'not_found', 'not_found'),
	(1,'Test conf file not good',test_conf_not_good, 'bad_conf', 'test_secvential'),
	(2,'Test Secvential',test_sequential, 'conf_secvential', 'test_secvential'),
	(3,'Test Paralel',test_paralel, 'conf_paralel', 'test_paralel'),
	(4,'Test faild',test_failed, 'conf_failed', 'test_failed')
]




def main():

	for test in tests:
		test[2](test[3], test[4])


	
#	if len(sys.argv) < 2:
#		return
#	if sys.argv[1] == "failed":
#		test_failed(content, agents, tracks)
#	if sys.argv[1] == "secvential":
#		test_secvential(content, agents, tracks)
#	if sys.argv[1] == "paralel":
#		test_paralel(content, agents, tracks)


if __name__ == "__main__":
	main()
