import pandas as pd
import matplotlib.pyplot as plt

def plotBuildTreeAnalysis():
  data = pd.read_csv("GenralComparaison/BuildTree.csv")
  fig, axs = plt.subplots(5, figsize=(12, 10))
  axs[0].set_ylabel("Excution Time(ns)")
  axs[0].set_title("TW(BST) Build")
  axs[0].plot(data["Size"].values,
               data["TW(BST)"].values, c="red", label="TW(BST)")
  
  axs[1].set_ylabel("Excution Time(ns)")
  axs[1].set_title("SAI(BST) Build")
  axs[1].plot(data["Size"].values,
               data["SAI(BST)"].values, c="blue", label="SAI(BST)")
  
  axs[2].set_ylabel("Excution Time(ns)")
  axs[2].set_title("SAI(AVL) Build")
  axs[2].plot(data["Size"].values,
               data["SAI(AVL)"].values, c="pink", label="SAI(AVL)")
  
  axs[3].set_ylabel("Excution Time(ns)")
  axs[3].set_title("TW(AVL) Build")
  axs[3].plot(data["Size"].values,
               data["TW(AVL)"].values, c="orange", label="TW(AVL)")
  axs[4].set_ylabel("Excution Time(ns)")
  axs[4].set_title("TW(Btree) Build")
  axs[4].set_xlabel("Size")
  axs[4].plot(data["Size"].values,
               data["TW(Btree)"].values, c="green", label="TW(Btree)")
  fig.legend(loc=2)
  fig.show()

def plotUpdateAnalysis():
  data=pd.read_csv("GenralComparaison/update.csv")
  fig, axs = plt.subplots(3, figsize=(10, 10))
  axs[0].set_ylabel("Excution Time(ns)")
  axs[0].set_title("(BST) Update")
  axs[0].plot(data["Size"].values,
               data["BST"].values, c="red", label="(BST)")
  axs[1].set_ylabel("Excution Time(ns)")
  axs[1].set_title("(AVL) Update")
  axs[1].plot(data["Size"].values,
               data["AVL"].values, c="pink", label="(AVL)")
  
  axs[2].set_ylabel("Excution Time(ns)")
  axs[2].set_title("(Btree) Update")
  axs[2].set_xlabel("Size")
  axs[2].plot(data["Size"].values,
               data["Btree"].values, c="green", label="(Btree)")
  
  fig.legend(loc=2)
  fig.show()
  
def plotDeleteAnalysis():
  data=pd.read_csv("GenralComparaison/delete.csv")
  fig, axs = plt.subplots(3, figsize=(10, 10))
  axs[0].set_ylabel("Excution Time(ns)")
  axs[0].set_title("(BST) Delete")
  axs[0].plot(data["Size"].values,
               data["BST"].values, c="red", label="(BST)")
  axs[1].set_ylabel("Excution Time(ns)")
  axs[1].set_title("(AVL) Delete")
  axs[1].plot(data["Size"].values,
               data["AVL"].values, c="pink", label="(AVL)")
  
  axs[2].set_ylabel("Excution Time(ns)")
  axs[2].set_title("(Btree) Delete")
  axs[2].set_xlabel("Size")
  axs[2].plot(data["Size"].values,
               data["Btree"].values, c="green", label="(Btree)")
  
  fig.legend(loc=2)
  fig.show()
  
def plotInsertAnalysis():
  data=pd.read_csv("GenralComparaison/Insert.csv")
  fig, axs = plt.subplots(3, figsize=(10, 10))
  axs[0].set_ylabel("Excution Time(ns)")
  axs[0].set_title("(BST) Insert")
  axs[0].plot(data["Size"].values,
               data["BST"].values, c="red", label="(BST)")
  axs[1].set_ylabel("Excution Time(ns)")
  axs[1].set_title("(AVL) Insert")
  axs[1].plot(data["Size"].values,
               data["AVL"].values, c="pink", label="(AVL)")
  
  axs[2].set_ylabel("Excution Time(ns)")
  axs[2].set_title("(Btree) Insert")
  axs[2].set_xlabel("Size")
  axs[2].plot(data["Size"].values,
               data["Btree"].values, c="green", label="(Btree)")
  
  fig.legend(loc=2)
  fig.show()
  
def plotSearchAnalysis():
  data=pd.read_csv("GenralComparaison/Search.csv")
  fig, axs = plt.subplots(3, figsize=(10, 10))
  axs[0].set_ylabel("Excution Time(ns)")
  axs[0].set_title("(BST) Search")
  axs[0].plot(data["Size"].values,
               data["BST"].values, c="red", label="(BST)")
  axs[1].set_ylabel("Excution Time(ns)")
  axs[1].set_title("(AVL) Search")
  axs[1].plot(data["Size"].values,
               data["AVL"].values, c="pink", label="(AVL)")
  
  axs[2].set_ylabel("Excution Time(ns)")
  axs[2].set_title("(Btree) Search")
  axs[2].set_xlabel("Size")
  axs[2].plot(data["Size"].values,
               data["Btree"].values, c="green", label="(Btree)")
  
  fig.legend(loc=2)
  fig.show()
  

#%%
plotSearchAnalysis()
plotUpdateAnalysis()
plotBuildTreeAnalysis()
plotInsertAnalysis()
plotDeleteAnalysis()
#%%