def cons(x,y):
	s = a = b = None #防止作弊用
	text1 = x
	text2 = y
	def gprint(num):
		if num == 1:
			return text2
		elif num == 0:
			return text1
		else:
			return "error"
	return gprint
    

		
