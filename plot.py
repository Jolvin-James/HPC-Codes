import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("merge_sort_results.csv")

plt.plot(data["Data Size"], data["Serial Time"], marker='o', label="Serial Merge Sort")
plt.plot(data["Data Size"], data["Parallel Time"], marker='o', label="Parallel Merge Sort")

plt.xlabel("Input Size")
plt.ylabel("Time (seconds)")
plt.title("Serial vs Parallel Merge Sort Performance")
plt.legend()
plt.grid(True)

plt.show()
