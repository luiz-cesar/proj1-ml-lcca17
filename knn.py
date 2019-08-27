import sys
import numpy
import math
from collections import Counter

def calculateMatch(test_array, data, realClass, k):
    distances = numpy.array([float("inf")] * k)
    objClass = [None] * k
    for objData in data:
        diff = math.sqrt(numpy.sum(numpy.power(objData['data'] - test_array, 2)))
        if diff < numpy.amax(distances):
            index = numpy.argmax(distances)
            objClass[index] = objData['objClass']
            distances[index] = diff

    return numpy.bincount(objClass).argmax() == int(realClass)



training = open(sys.argv[1])
training_data = []
for line in training:
    space_separated = line.split()
    array = numpy.array(list(map(lambda string: float(string.split(":")[1]), space_separated[1:])))
    training_data.append({'objClass': space_separated[0], 'data': array})
training.close()


test = open(sys.argv[2])
k = int(sys.argv[3])
corrects = 0
all = 0
for line in test:
    space_separated = line.split()
    array = numpy.array(list(map(lambda string: float(string.split(":")[1]), space_separated[1:])))
    all+=1
    if calculateMatch(array, training_data, space_separated[0], k):
        corrects+=1

test.close()
print(corrects / all)


