# import pandas as pd
# import matplotlib.pyplot as plt

# df = pd.read_csv('vector_add.csv')

# sizes = df['Data Size']
# serial_times = df['Serial']
# parallel_times = df['Parallel']

# plt.figure(figsize=(10, 6)) 

# plt.plot(sizes, serial_times, marker='o', label='Serial Execution', color='red', linestyle='--')

# plt.plot(sizes, parallel_times, marker='s', label='Parallel Execution', color='green', linewidth=2)

# plt.title('Performance Comparison: Serial vs Parallel Vector Addition')
# plt.xlabel('Data Size (N)')
# plt.ylabel('Time (seconds)')
# plt.legend() 
# plt.grid(True) 


# plt.show() 

import pandas as pd
import matplotlib.pyplot as plt

try:
    df = pd.read_csv('vector.csv')
except FileNotFoundError:
    print("Error: 'vector_results.csv' not found. Please ensure the file exists.")
    exit()

plt.figure(figsize=(10, 6))

plt.plot(df['Data Size'], df['Serial Time'], marker='o', linestyle='-', label='Serial Time')
plt.plot(df['Data Size'], df['Parallel Time'], marker='s', linestyle='-', label='Parallel Time')


plt.xscale('log')
plt.yscale('log') 

plt.title('Vector Addition Performance: Serial vs Parallel (OpenMP)', fontsize=14)
plt.xlabel('Data Size (N) - Log Scale', fontsize=12)
plt.ylabel('Execution Time (seconds) - Log Scale', fontsize=12)
plt.grid(True, which="both", linestyle='--', alpha=0.7)
plt.legend()

plt.tight_layout()
plt.savefig('performance_comparison.png')
plt.show()

df['Speedup'] = df['Serial Time'] / df['Parallel Time']
print("\nPerformance Summary:")
print(df[['Data Size', 'Serial Time', 'Parallel Time', 'Speedup']])