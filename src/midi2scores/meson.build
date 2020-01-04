inc = include_directories(['include',])

# Librería MIDIFILE

src = [
    'src/midi2skini.cpp',
    'src/FileIO.cpp',
    'src/MidiFile.cpp',
    'src/Options.cpp',
    'src/Options_private.cpp',
]

###########################################################################
#                                                                         #
# Hemos de determinar si el sistema operativo es Linux, Mac OS X u otro   #
#                                                                         #
###########################################################################
#                                                                         #
#  Operating System OSTYPEs available in the Midifile library             #
#  compilation:                                                           #
#                                                                         #
#      HPUX   = Hewlett-Packard Unix Workstations.                        #
#      IRIX   = SGI computers with IRIX OS.                               #
#      LINUX  = Linux running on intel computers                          #
#      NEXTI  = NeXT OS on Intel Hardware                                 #
#      NEXTM  = NeXT OS on Motorola Hardware                              #
#      OSXPC  = Apple Macintosh OS 10.x, Intel CPU                        #
#      OSXOLD = Apple Macintosh OS 10.x, PowerPC CPU                      #
#      SUN    = Sun SPARCstations                                         #
#      VISUAL = Windows 95/NT using Microsoft Visual C++ 6.0              #
#                                                                         #
# Look at the sigConfiguration.h file for various things which need       #
# to be defined specifically for each OS.  Only one of these defines      #
# can be defined at a time.                                               #
#                                                                         #
###########################################################################
#                                                                         #
# En el caso de Linux y Mac OS X funcionando en Motorola o Intel, las     #
# órdenes siguientes deberían detectarlo automáticamente                  #
#                                                                         #
###########################################################################

system = host_machine.system()
if system == 'linux'
    cpp_args = ['-DLINUX']
elif system == 'darwin'
    cpp_args = ['-DOSXPC']
    if host_machine.cpu_family().contains('x86')
         cpp_args += ['-m32', '-arch', 'x86_64']
    endif
else
	warning('La arquitectura "@0@" no está soportada,'.format(system))
	warning('edita el fichero meson.build para incluirla.')
endif

executable(
    'midi2skini',
    sources: src,
    include_directories: inc,
    link_args: ['-lm', '-lsndfile'],
    cpp_args: cpp_args,
    install: true,
)

midi2sco = 'midi2sco.py'
source = join_paths(meson.source_root(), 'src/midi2scores', midi2sco)   # Ruta completa
prog = midi2sco.split('.')[0]                                             # Nombre sin extensión
dest = join_paths(get_option('prefix'), get_option('bindir'), prog)
custom_target(midi2sco,
    input : source,
    output : prog,
    command : ['ln', '-sf', source, dest],
    build_by_default: true,
)

cpp_args = []
