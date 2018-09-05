import os
import sys

def testRequestsPerAgent(content, agents):

	max_time = int(content[-3].split(":")[0])
	agents_time = []
	tracks_time = []
	for agent in agents:	
		agents_time.append([0] * max_time)

	for line in content:
		if "REQUEST" not in line:
			continue
		time = int(line[0:4])
		req_id = line.split("---")[1].split(":")[1]
		agent_id = line.split("---")[2].split(":")[1]
		track_id = line.split("---")[3].split(":")[1].strip("\n")
		print(time, req_id, agent_id, track_id)


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
	testRequestsPerAgent(content,agents)

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
	testRequestsPerAgent(content,agents)

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


	print(agents)
	print(tracks)

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
