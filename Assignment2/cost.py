
capacity = 8
print("N:\tO(n)")
for N in range(500, 600):
	totalCost = capacity
	for x in range(totalCost, N):
		if x%2 == 0:
			totalCost += 1
		else:
			totalCost += x
	print(str(N) + "\t" + str(totalCost/N))
