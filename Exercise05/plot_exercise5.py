import matplotlib.pyplot as plt
import pandas as pd

# Read Fibonacci OpenMP data
fib = pd.read_csv('fib_timing.csv')
plt.figure(figsize=(8,5))
plt.plot(fib['Threads'], fib['Time'], marker='o')
plt.xlabel('Number of Threads')
plt.ylabel('Time (s)')
plt.title('Fibonacci (OpenMP) Time vs Threads')
plt.grid(True)
plt.savefig('fib_time_vs_threads.png')
plt.show()

# Compute and plot Speedup
fib['Speedup'] = fib['Time'][0] / fib['Time']
plt.figure(figsize=(8,5))
plt.plot(fib['Threads'], fib['Speedup'], marker='o', color='red')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup')
plt.title('Fibonacci (OpenMP) Speedup')
plt.grid(True)
plt.savefig('fib_speedup.png')
plt.show()

# Read MPI Sum data
sum_mpi = pd.read_csv('sum_timing.csv')
plt.figure(figsize=(8,5))
plt.plot(sum_mpi['Processes'], sum_mpi['Time'], marker='o')
plt.xlabel('Number of Processes')
plt.ylabel('Time (s)')
plt.title('MPI Sum Time vs Processes')
plt.grid(True)
plt.savefig('sum_time_vs_processes.png')
plt.show()

# Compute and plot Speedup
sum_mpi['Speedup'] = sum_mpi['Time'][0] / sum_mpi['Time']
plt.figure(figsize=(8,5))
plt.plot(sum_mpi['Processes'], sum_mpi['Speedup'], marker='o', color='red')
plt.xlabel('Number of Processes')
plt.ylabel('Speedup')
plt.title('MPI Sum Speedup')
plt.grid(True)
plt.savefig('sum_speedup.png')
plt.show()
