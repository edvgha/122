import sys
import cvxpy as cvx
import cv2
import numpy as np
from matplotlib import pyplot as plt

def de_noising(in_image, out_image):
    #read image in
    img = cv2.imread(in_image, cv2.IMREAD_GRAYSCALE)
    m, n = img.shape
    #generate noise
    np.random.seed(1)
    Known1 = (np.random.rand(m, n) > 0.15).astype(int)
    Known2 = (np.random.rand(m, n) <= 0.15).astype(int)
    obs = np.multiply(img , Known1) + 106 * Known2
    cv2.imwrite('hopar_noisy.png',obs)
    #define interpolation variable
    inter = cvx.Variable((m, n))
    #minimize total variation
    prob = cvx.Problem(cvx.Minimize(cvx.tv(inter)), [cvx.multiply(inter, Known1) == cvx.multiply(img, Known1)])
    print ('----> solver starts')
    result = prob.solve()
    #write image out
    cv2.imwrite(out_image, inter.value)

def main():
    de_noising('hopar.png', 'hopar_de_noised.png')

if __name__ == '__main__': main()
