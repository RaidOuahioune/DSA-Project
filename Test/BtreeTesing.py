import pandas as pd
import matplotlib.pyplot as plt

colors = ["red", "green", "blue", "pink", "purple"]


def plotAnalysis(file):
    data = pd.read_csv(f"BtreeComparaison/{file}.csv")
    fig, axs = plt.subplots(5, figsize=(10, 10))
    for i in [0, 1, 2, 3, 4]:
        if (i == 4):
            axs[i].set_xlabel("Size")
        if(i==0):
          axs[i].set_title(file)
        axs[i].set_ylabel("Excution Time")

        axs[i].plot(data["Size"].values,
                    data[f"Order{i+2}"].values, c=colors[i], label=f"Order{i+2}")

    fig.legend(loc=2)
    fig.show()


files = ["BuildTree", "delete", "Insert", "Search", "update"]
# %%
for file in files:
    plotAnalysis(file)
# %%
