import myScalar
import myMatrix

class myString:

	def __init__(self, val):
		# check the input parameter
		if type(val) != str:
			raise NameError('Initialization Fail')
		# member variable assign
		self.val = val
		
	def __str__(self): # Make myString to string value for scoring
		return self.val

############ do not change the above lines ############

	def addScalar(self, op): # string + scalar를 overloading 해준다.
		return self.val + str(op.val)

	def mulScalar(self, op): # scalar * string 계산을 진행해준다.

		if op.val < 0: # op가 음수일 경우
			num = int(op.val / 1)
			rev = self.val[::-1]
			t = myString('')

			for i in range(-1 * num):
				t.val = t.val + rev
			return t

		else: # op가 0 이상일 경우
			num = int(op.val / 1)
			t = myString('')


			for i in range(num):
				t.val = t.val + self.val
			return t

	def __add__(self, op): # add를 magic method를 통해 overloading 해준다
		if type(op) is myScalar.myScalar:
			return self.addScalar(op)
		if type(op) is myString:
			return self.val + op.val
		else:
			raise NameError('Not defined')

	def __mul__(self, op): # mul를 magic method를 통해 overloading 해준다
		if type(op) is myScalar.myScalar:
			return self.mulScalar(op)
		else:
			raise NameError('Not defined')

	def __sub__(self, op): # sub은 계산할 수 없다.
		raise NameError('Not defined')

	def __div__(self, op): # div은 계산할 수 없다.
		raise NameError('Not defined')









