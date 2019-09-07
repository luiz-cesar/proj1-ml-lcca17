#!/usr/bin/python
# -*- encoding: iso-8859-1 -*-

import sys
import numpy
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import confusion_matrix
from sklearn.datasets import load_svmlight_file
from sklearn import preprocessing
# import pylab as pl


def main(train_data, test_data):

    # loads data
    # print "Loading data..."
    X_train, y_train = load_svmlight_file(train_data)

    X_train = X_train.toarray()

    # fazer a normalizacao dos dados #######
    #scaler = preprocessing.MinMaxScaler()
    #X_train = scaler.fit_transform(X_train_dense)
    #X_test = scaler.fit_transform(X_test_dense)

    # cria um kNN
    neigh = KNeighborsClassifier(n_neighbors=1, metric='euclidean')

    # print 'Fitting knn'
    neigh.fit(X_train, y_train)

    X_test, y_test = load_svmlight_file(test_data)
    X_test = X_test.toarray()

    # predicao do classificador
    # print 'Predicting...'
    y_pred = neigh.predict(X_test)

    # mostra o resultado do classificador na base de teste
    print neigh.score(X_test, y_test)

    # cria a matriz de confusao
    cm = confusion_matrix(y_test, y_pred)
    print cm

    # pl.matshow(cm)
    # pl.colorbar()
    # pl.show()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Use: knn.py <training_data> <testing_data>")

    main(sys.argv[1], sys.argv[2])
