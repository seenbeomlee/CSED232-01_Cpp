import myString
import myMatrix

class myScalar:

	def __init__(self, val):
		# check the input parameter
		if type(val)!=float:
			raise NameError('Initialization Fail')
		# member variable assign
		self.val = val

	def __str__(self): # Make myScalar to string value for scoring
		return str(self.val)

############ do not change the above lines ############

	def addStr(self,op): # scalar + string
		res = myString.myString('')
		return myString.myString(str(self.val)+op.val)

	def __add__(self, op): # add를 magic method를 통해 overloading 해준다
		if type(op) is myScalar:
			return myScalar(self.val+op.val)
		elif type(op) is myMatrix.myMatrix:
			return (op + self)
		elif type(op) is myString.myString:
			return self.addStr(op)
		else:
			raise NameError('Not defined')
	##

	def __sub__(self, op): # sub를 magic method를 통해 overloading 해준다
		if type(op) is myScalar:
			return myScalar(self.val-op.val)
		elif type(op) is myMatrix.myMatrix:
				res = myMatrix.myMatrix(op.row, op.col)
				for i in range(len(op.val)):
					for j in range(len(op.val[i])):
						res.val[i][j] = self.val - op.val[i][j]
				return (res)
		else:
			raise NameError('Not defined')

	def __mul__(self, op): # mul를 magic method를 통해 overloading 해준다
		if type(op) is myScalar:
			return myScalar(self.val*op.val)
		elif type(op) is myMatrix.myMatrix:
			return (op * self)
		elif type(op) is myString.myString:
			return (op * self)
		else:
			raise NameError('Not defined')

	def __truediv__(self, op): # div를 magic method를 통해 overloading 해준다
		if type(op) is myScalar:
			return myScalar(self.val/op.val)
		else:
			raise NameError('Not defined')

	def __mod__(self, op):
		return self.val % op

	def __lt__(self, op): # lt를 magic method를 통해 overloading 해준다 / myScalar가 음수인지 혹은 0, 양수인지 구분할 때
		return self < op





