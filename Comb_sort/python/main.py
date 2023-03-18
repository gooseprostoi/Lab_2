import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

plt.figure(figsize=(12, 6))

# time
plt.subplot(121)
data = pd.read_csv("time_data.txt", sep="\t")
N = data.iloc[:, 0]
t = data.iloc[:, 1]
N = N.to_numpy()
t = t.to_numpy()

plt.title('Время сортировки')
plt.xlabel('$N$, элементов', fontsize=14)
plt.ylabel('$t$, мс', fontsize=14)
p = np.polyfit(N, t, deg=2)
p_f = np.poly1d(p)
X = np.arange(0, 25000, 0.1)
plt.plot(X, p_f(X))
print(p)

plt.scatter(N, t, marker="s", color="black",s=10)
plt.grid()



# transpositions

plt.subplot(122)
data = pd.read_csv("transposition_data.txt", sep="\t")
N = data.iloc[:, 0]
t = data.iloc[:, 1]
N = N.to_numpy()
t = t.to_numpy()

plt.title('Количество перестановок сортировки')
plt.xlabel('$N$, элементов', fontsize=14)
plt.ylabel(r'количество транспозиций, $1 = 10^8$', fontsize=14)
p = np.polyfit(N, t, deg=2)
p_f = np.poly1d(p)
X = np.arange(0, 25000, 0.1)
plt.plot(X, p_f(X))
print(p)

plt.scatter(N, t, marker="s", color="black", s=10)
plt.grid()
plt.show()
