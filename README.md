# AmongUsLists
A simulation of Among Us game using linked lists.
# Prerequisites
- Make || apt install make
- gcc || apt install gcc
# Run
Place your txt under tests folder then use:
**./run.sh "your.txt"**

**run.sh formats:**
- "-h" for help
- "-c" for clean
- "your.txt" to run.

**your.txt format:**
*There are 15 cases that each line of the input file can have...*

- Comment: '#' 
- Register player: 'P <pid><is_alien>'
- Insert task: 'T <tid><difficulty>'
- Distribute Tasks: 'D'
- Implement Task: 'I <pid> <difficulty>'
- Eject Player: 'E <pid>'
- Witness Ejection: 'W <pid> <pid_a> <number_of_witnesses>'
- Sabbotage: 'S <number_of_tasks><pid>'
- Vote: '<pid> <vote_evidence>'
- Give Away Work: 'G'
- Terminate: 'F'
- Print Players: 'X'
- Print Tasks: 'Y'
- Print Stack 'Z'
- Print Players & Tasks list: 'F'
- Empty line: '\n'

***see tests folder example***
