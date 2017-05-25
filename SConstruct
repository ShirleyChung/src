env = Environment() 

env.Append(CPPPATH=['#classes','#h'])

#common library
sc = SConscript( dirs = 'classes', exports = 'env' )

#main tester
system = SConscript( dirs='system', exports = ['env','sc'] )

man = SConscript( dirs='man', exports = 'env' )
talker = SConscript( dirs='talker', exports = 'env' )
annmind = SConscript( dirs='annmind', exports = 'env' )

#socket programs
server = SConscript( dirs='server', exports = 'env' )
client = SConscript( dirs='client', exports = 'env' )

#MUDs
muds = SConscript( dirs=['chatroom', 'login', 'mud', 'conui'], exports = 'env' )

