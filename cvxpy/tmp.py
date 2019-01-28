import numpy

a = numpy.matrix([[1,1,1],[1,1,1],[1,1,1]])
b = numpy.matrix([[2,2],[2,2],[2,2]])
c = numpy.matrix([[3,3,3],[3,3,3]])
d = numpy.matrix([[4,4],[4,4]])

x = numpy.concatenate((a, b), axis = 1)
y = numpy.concatenate((c, d), axis = 1)

z = numpy.concatenate((x, y), axis = 0)

arr = numpy.array([1, 2, 3, 4, 5, 6, 7, 8, 9])

print (arr[0:5])

arr1 = numpy.array([1, 2, 3])
arr2 = numpy.array([1, 1, 1])

print (numpy.dot(arr1.T, arr2))

if min(arr1  + 1 * arr2) >= 3:
    print  ("valod")

print ("----------------------")
x = numpy.array([1, 2, 3, 4]);
print (numpy.exp(x))
print ("----------------------")
a = numpy.matrix([[1,0,0],[0,1,0],[0,0,1]])
b = numpy.matrix([[1,0,0],[0,2,0],[0,0,3]])
c = numpy.matrix([[1,0,0],[0,2,0],[0,0,3]])

print (numpy.dot(a, b, c))
print ("---------------------")
x = numpy.array([1, 2, 3, 4]);
y = numpy.array([1, 2, 3, 4]);
print (x * y)
