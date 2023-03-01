# -*- coding: utf-8 -*-
"""SMVM_3lab.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1lLRGCAFnTDW7dCCV0KGXkKuh2AKIidv-
"""

import numpy as np
import matplotlib.pyplot as plt
import time as time
import copy
import timeit
import pandas as pd

Num_of_grids = 9
g = 9.81 #уск. своб. падения
force = 30000 #сила
E = 30 * (10**9) #модуль упругости
rho = 2150*(10**3) #плотность
A = 0.0341 #постоянная площадь поперечного сечения
neimann_cond = -force/(E*A) #краевое условие
f = rho*g*A
L = 5 # длина балки

def exact(x):
    return (rho*g*A*(x**2))/(2*E*A) - ((force+rho*g*A*L)/(E*A))*x 

def psi(x, i, x_arr):
    l = x_arr[1] - x_arr[0]
    if i != len(x_arr)-1:
        if x >= x_arr[i] and x <= x_arr[i+1]:
            return (x_arr[i+1] - x)/l
    if i != 0:
        if x > x_arr[i-1] and x <= x_arr[i]:
            return (x - x_arr[i-1])/l
    return 0

def approx(x, u, N):
    x_arr = np.linspace(0,L,N+1)
    res = 0
    for i in range(N+1):
        res += u[i]*psi(x,i,x_arr)
    return res

def K(coef, l, N,neimann_cond):
    K = np.zeros((N+1, N+1))
    k_small = np.array([[1,-1],[-1,1]])
    for i in range(N):
        K[i:i+2,i:i+2] += k_small
    K[0] = np.zeros(N+1)
    K[0,0] = 1
    K *= coef / l
    return K


def P(coef, l, N, neimann_cond):
    K = np.zeros((N+1, N+1))
    k_small = np.array([[2,1],[1,2]])
    for i in range(N):
        K[i:i+2,i:i+2] += k_small
    K[0] = np.zeros(N+1)
    K = -K * l / 6
    return K

def errors(u, N, L):
    Q = 10000
    mmax = 0
    err_L2 = 0
    for x in np.linspace(0,L,Q, endpoint=False):
        err = abs(exact(x) - approx(x, u, N))
        mmax = max(err, mmax)
        err_L2 += (exact(x) - approx(x, u, N))**2

    x = np.linspace(0,L,Q, endpoint=False)
    mmax_sol = max(np.abs(exact(x)))
    exact_norm = exact(x).dot(exact(x))
    rel_error_L2 = np.sqrt(err_L2/exact_norm)
    rel_err_inf = mmax / mmax_sol
    
    return rel_err_inf, rel_error_L2

K_cond = np.zeros(Num_of_grids)
L2_error_tab = np.zeros(Num_of_grids)
rel_error_tab = np.zeros(Num_of_grids)
L2_rate = np.zeros(Num_of_grids)
rel_rate = np.zeros(Num_of_grids)

time_tab = np.zeros(Num_of_grids)

Q = 10000
x_fine = np.linspace(0, L, Q)

for i in range(Num_of_grids):
    N = 5 * 2**i
    start = time.time()
    x = np.linspace(0, L, N+1) # element edges
    
    l = L/N

    P_ = P(E*A, l, N, neimann_cond)
    K_ = K(E*A, l, N, neimann_cond)

    left_vec = P_.dot(np.ones(N+1)*f)
    left_vec[-1] += neimann_cond*E*A

    u = np.linalg.solve(K_, left_vec)
    time_tab[i] = time.time() - start
    K_cond[i] = np.linalg.cond(K_)
    u = exact(x) 

    rel_error_tab[i], L2_error_tab[i] = errors(u, N, L)
    
    fig, ax = plt.subplots(1)
    SIZE = 12
    ax.plot(x_fine, exact(x_fine))
    ax.plot(x, u, linestyle = '--')
    
    ax.legend(['Точное решение', 'Аппроксимация N='+str(N)])
    ax.set_xlabel('x', fontsize = SIZE)
    ax.set_ylabel('u(x)', fontsize = SIZE)
    plt.show()

for i in range(1,Num_of_grids):
    L2_rate[i] = np.log(L2_error_tab[i-1]/L2_error_tab[i]) / np.log(2)
    rel_rate[i] = np.log(rel_error_tab[i-1]/rel_error_tab[i]) / np.log(2)

data = [rel_error_tab, rel_rate, L2_error_tab,L2_rate, K_cond, time_tab]
pd.set_option("precision", 2)
df = pd.DataFrame(np.transpose(data))

def exact(x):
    return (rho*g*A*(x**2))/(2*E*A) - ((force+rho*g*A*L)/(E*A))*x
    
fig, ax = plt.subplots(1)
SIZE = 12
ax.plot(x_fine, exact(x_fine))
plt.show()
print(exact(x_fine))

df

u

