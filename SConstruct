env = Environment() 

#common library
sc = SConscript( dirs = 'classes', exports = 'env' )

#main tester
system = SConscript( dirs='system', exports = ['env','sc'] )

man = SConscript( dirs='man', exports = 'env' )
talker = SConscript( dirs='talker', exports = 'env' )

#socket programs
server = SConscript( dirs='server', exports = 'env' )
client = SConscript( dirs='client', exports = 'env' )

#MUDs
chatroom = SConscript( dirs='chatroom', exports = 'env' )
login = SConscript( dirs='login', exports = 'env' )
mud = SConscript( dirs='mud', exports = 'env' )
conui = SConscript( dirs='conui', exports = 'env' )
