import pickle
list=[]

fout = open("books.pickle", "wb")
pickle.dump(list, fout)
fout.close()
