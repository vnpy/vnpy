
class VNPAST_ConfigError(Exception):
	"""
	Config file error, raised when config.json or python object
	is broken or invalid.

	"""
	pass

class VNPAST_RequestError(Exception):
	"""
	HTTP Request Error, raised when response is not properly gotten:
	* GET response.status code != 200.
	* POST response.status code != 201.
	* Connection timed out.
	* ...

	"""
	pass

class VNPAST_DatabaseError(Exception):
	"""


	"""
	pass

class VNPAST_DataConstructorError(Exception):
	"""


	"""
	pass