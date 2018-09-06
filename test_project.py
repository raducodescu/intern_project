import os
import sys

def testRequestsPerAgent(content, agents, tracks):

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
			assert loading <= cap
			assert loading >= 0

	for track in tracks_time:
		for time in track[1]:
			assert time < 2
			assert time >= 0	


def test_failed(content, agents, tracks):
	failed = 0
	success = 0
	receive = 0

	for line in content:
		if "RECEIVE REQUEST" in line:
			receive = receive + 1
		elif "FAILED REQUEST" in line:
			failed = failed + 1
		elif "SUCCESS REQUEST" in line:
			success = success + 1

	assert failed == 6
	assert success == 6
	assert receive == 6

def test_secvential(content, agents, tracks):
	failed = 0
	success = 0
	receive = 0

	for line in content:
		if "RECEIVE REQUEST" in line:
			receive = receive + 1
		elif "FAILED REQUEST" in line:
			failed = failed + 1
		elif "SUCCESS REQUEST" in line:
			success = success + 1

	assert failed == 0
	assert success == 10
	assert receive == 10
	testRequestsPerAgent(content,agents,tracks)

def test_paralel(content, agents, tracks):
	failed = 0
	success = 0
	receive = 0

	for line in content:
		if "RECEIVE REQUEST" in line:
			receive = receive + 1
		elif "FAILED REQUEST" in line:
			failed = failed + 1
		elif "SUCCESS REQUEST" in line:
			success = success + 1

	assert failed == 0
	assert success == 18
	assert receive == 18
	testRequestsPerAgent(content,agents,tracks)

def main():
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

	if len(sys.argv) < 2:
		return
	if sys.argv[1] == "failed":
		test_failed(content, agents, tracks)
	if sys.argv[1] == "secvential":
		test_secvential(content, agents, tracks)
	if sys.argv[1] == "paralel":
		test_paralel(content, agents, tracks)


if __name__ == "__main__":
	main()
