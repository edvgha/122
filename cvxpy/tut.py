import cvxpy as cvx
import numpy

a = cvx.Variable(3, value = [2,2,2]);
b = cvx.log(a)
mm = a.T * b
tt = cvx.sum(mm)

print (a.value)
print (b.value)
print  (mm.value)
print  (tt.value)


# Create two scalar optimization variables.
x = cvx.Variable()
y = cvx.Variable()

# Create two constraints.
constraints = [x + y == 1,
               x - y >= 1]

# Form objective.
obj = cvx.Minimize((x - y)**2)

# Form and solve problem.
prob = cvx.Problem(obj, constraints)
prob.solve()  # Returns the optimal value.
print("status:", prob.status)
print("optimal value", prob.value)
print("optimal var", x.value, y.value)

print("---------------------")

# Replace the objective.
prob2 = cvx.Problem(cvx.Maximize(x + y), prob.constraints)
print("optimal value", prob2.solve())

print("---------------------")

# Replace the constraint (x + y == 1).
constraints = [x + y <= 3] + prob2.constraints[1:]
prob3 = cvx.Problem(prob2.objective, constraints)
print("optimal value", prob3.solve())
