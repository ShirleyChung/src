env = Environment() 
#Repository('h','classes')

sc = SConscript( dirs = 'classes', exports = 'env' )

system = SConscript( dirs='system', exports = ['env','sc'] )

man = SConscript( dirs='man', exports = 'env' )

talker = SConscript( dirs='talker', exports = 'env' )

server = SConscript( dirs='server', exports = 'env' )

client = SConscript( dirs='client', exports = 'env' )

