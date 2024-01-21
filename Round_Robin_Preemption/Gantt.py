import matplotlib.pyplot as plt

processes = []
with open('processes.txt', 'r') as file:
    for line in file:
        pid, arrival, start, burst, end, tat, wt, rt = map(int, line.split())
        processes.append((pid, start, end - start))

fig, gnt = plt.subplots()

gnt.set_xlabel('Time')
gnt.set_ylabel('Processes')

gnt.set_yticks([p[0] for p in processes])
gnt.set_yticklabels([f'P{p[0]}' for p in processes])

for i, (pid, start, duration) in enumerate(processes):
    gnt.broken_barh([(start, duration)], (i, 1), facecolors=('red'))

plt.title('Gantt Chart')
plt.show()