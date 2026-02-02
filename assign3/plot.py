import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('bubble_result.csv')

plt.figure(figsize=(10, 6))
plt.plot(df['Data Size'], df['Serial'], label='Serial Time', marker='o')
plt.plot(df['Data Size'], df['Parallel'], label='Parallel Time', marker='x')

plt.xlabel('Data Size')
plt.ylabel('Time (seconds)')
plt.title('Performance Comparison: Serial vs Parallel Bubble Sort')
plt.legend()
plt.grid(True)

plt.show()