import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('merge_result.csv')

plt.figure(figsize=(10, 6))

plt.plot(df['Size'], df['Serial(I)'], marker='o', linestyle='-', label='Serial Non Recursive')
plt.plot(df['Size'], df['Parallel(I)'], marker='o', linestyle='-', label='Parallel Non Recursive')

plt.plot(df['Size'], df['Serial R'], marker='o', linestyle='--', label='Serial Recursive')
plt.plot(df['Size'], df['Parallel R'], marker='o', linestyle='--', label='Parallel Recursive')

plt.title('Input Size vs Time Taken (Non-Recursive vs Recursive)')
plt.xlabel('Input Size')
plt.ylabel('Time Taken (s)')
plt.legend()
plt.grid(True)

plt.show()