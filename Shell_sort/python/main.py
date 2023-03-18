import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

plt.figure(figsize=(8, 6))

data = pd.read_csv("time_data3.txt", sep="\t")
N = data.iloc[:, 0]
t = data.iloc[:, 1]
N = N.to_numpy()
t = t.to_numpy()
t = np.log(t)
N = np.log(N)

plt.title('Сортировка 3')
plt.xlabel(r'$\ln N$', fontsize=14)
plt.ylabel(r'$\ln t$', fontsize=14)
p = np.polyfit(N, t, deg=1)
p_f = np.poly1d(p)
X = np.arange(9.3, 11.8, 0.1)
plt.plot(X, p_f(X))
print(p)

plt.scatter(N, t, marker="s", color="black",s=7)
plt.grid()

data = pd.read_csv("transposition_data3.txt", sep="\t")
t = data.iloc[:, 1]
t = t.to_numpy()
print(t.mean())

plt.show()
