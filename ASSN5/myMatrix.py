import myScalar
import myString

class myMatrix:

	# for initialize empty matrix
	def __initEmpty(self, row, col):
		if row <=0 or col <= 0:
			raise NameError('Initialization Fail')
		self.row = row
		self.col = col
		self.val = [([float()] * col) for i in range(row)]

	def __init__(self, row, col, val=[]):
		# for empty matrix
		if not val:
			self.__initEmpty(row,col)
			return
		# check the input parameter
		if type(val)!=list or not all(isinstance(v,float) for v in val) or len(val)!=row*col or row <=0 or col <= 0:
			raise NameError('Initialization Fail')
		# member variable assign
		self.row = row
		self.col = col
		self.val = []
		for i in range(row):
			self.val.append([])
			for j in range(col):
				self.val[i].append(val[col*i+j])

	def __str__(self): # Make myMatrix to string value for scoring
		return str(self.val)

############ DO NOT change the above lines ############

	def addScalar(self,op): # myMatrix + myScalar를 계산해준다.
		res = myMatrix(self.row,self.col)
		for i in range(len(self.val)):
			for j in range(len(self.val[i])):
				res.val[i][j] = self.val[i][j] + op.val
		return res

	def subScalar(self,op):  # myMatrix - myScalar를 계산해준다.
		res = myMatrix(self.row,self.col)
		for i in range(len(self.val)):
			for j in range(len(self.val[i])):
				res.val[i][j] = self.val[i][j] - op.val
		return res

	def mulScalar(self,op):  # myMatrix * myScalar를 계산해준다.
		res = myMatrix(self.row,self.col)
		for i in range(len(self.val)):
			for j in range(len(self.val[i])):
				res.val[i][j] = self.val[i][j] * op.val
		return res

	def divScalar(self,op):  # myMatrix / myScalar를 계산해준다. 단, myScalar에는 정의를 안해놓았기 때문에 역은 성립x
		res = myMatrix(self.row,self.col)
		for i in range(len(self.val)):
			for j in range(len(self.val[i])):
				res.val[i][j] = self.val[i][j] // op.val
		return res

	def addMatrix(self,op):  # myMatrix + myMatrix를 계산해준다.
		res = myMatrix(self.row,self.col)
		if self.row != op.row or self.col != op.col:
			raise NameError('Dimension mismatch') # dimension 이 맞지 않을 경우 error 출력

		for i in range(len(self.val)):
			for j in range(len(self.val[i])):
				res.val[i][j] = self.val[i][j] +op.val[i][j]
		return res

	def subMatrix(self, op): # myMatrix - myMatrix를 계산해준다.
		res = myMatrix(self.row, self.col)
		if self.row != op.row or self.col != op.col:
			raise NameError('Dimension mismatch')

		for i in range(len(self.val)):
			for j in range(len(self.val[i])):
				res.val[i][j] = self.val[i][j] - op.val[i][j]
		return res

	def mulMatrix(self, op): # myMatrix * myMatrix를 계산해준다.
		res = myMatrix(self.row, op.col) # 2x3 * 3x2 라면 res = 2x2 matrix가 된다.
		if self.row != op.col or self.col != op.row:
			raise NameError('Dimension mismatch') # dimension이 맞지 않을 경우 error 출력

		for i in range(self.row):
			for j in range(op.col):
				for k in range(self.col):
					res.val[i][j] = res.val[i][j] + self.val[i][k] * op.val[k][j] # *계산 진행
		return res

	def __add__(self, op): # add를 magic method를 통해 overloading 해준다
		if type(op) is myScalar.myScalar:
			return self.addScalar(op)
		elif type(op) is myMatrix:
			return self.addMatrix(op)
		else:
			raise NameError('Not defined')

	def __sub__(self, op): # sub를 magic method를 통해 overloading 해준다
		if type(op) is myScalar.myScalar:
			return self.subScalar(op)
		elif type(op) is myMatrix:
			return self.subMatrix(op)
		else:
			raise NameError('Not defined')

	def __mul__(self, op): # mul를 magic method를 통해 overloading 해준다
		if type(op) is myScalar.myScalar:
			return self.mulScalar(op)
		elif type(op) is myMatrix:
			return self.mulMatrix(op)
		else:
			raise NameError('Not defined')

	def __truediv__(self, op): # truediv를 magic method를 통해 overloading 해준다
		if type(op) is myScalar.myScalar:
			return self.divScalar(op)
		else:
			raise NameError('Not defined')


