from sympy import *
import math


def trapezoid(a: float, b: float, n: int, f: core) -> float:
    h = (b - a) / n
    w = 0
    for k in range(1, n - 1):
        x_local = a + k * h
        w = w + f.subs(x, x_local)
    w = (2 * w + (f.subs(x, a)).evalf() + f.subs(x, b).evalf()) * h / 2
    return w


# n = 8
def trapezoid_simpson(a: float, b: float, m: int, f: core) -> float:
    n = 2 * m
    h = (b - a) / n
    s = 0
    s1 = 0
    s2 = 0
    for k in range(1, m):
        x_local = a + (2 * k + 1) * h
        s1 = s1 + f.subs(x, x_local)
    for k in range(1, m - 1):
        x_local = a + 2 * k * h
        s2 = s2 + f.subs(x, x_local)
    s = (4 * s1 + 2 * s2 + f.subs(x, a).evalf() + f.subs(x, b).evalf()) * h / 3
    return s


# a) 1/(sqrt(2 * x ** 2 + 5)) (1.2 - 2)
# b) cos(x ** 2)/(x ** 2 + 1) (0.2 - 1)
# epsilon = 0.001, если у величить в 2-3 порядка - вычисления будут слишком долгими
eps = 0.001
x = symbols('x')
# Решение премера под буквой а)
fa = 1 / (sqrt(2 * x ** 2 + 5))
a = 1.2
b = 2
n = 1
f1 = trapezoid(a, b, n, fa)
n = n * 2
f2 = trapezoid(a, b, n, fa)
while abs(f1 - f2) > eps:
    f1 = f2
    n = n * 2
    f2 = trapezoid(a, b, n, fa)
print(f2)

# Решение премера под буквой б)
x = symbols('x')
fb = cos(x ** 2)/(x ** 2 + 1)
a = 0.2
b = 1
n = 1
f1 = trapezoid_simpson(a, b, n, fb)
n = n * 2
f2 = trapezoid_simpson(a, b, n, fb)
while abs(f1 - f2) > eps:
    f1 = f2
    n = n * 2
    f2 = trapezoid_simpson(a, b, n, fa)
print(f2)

