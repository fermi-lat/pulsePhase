# -*- python -*-
# $Id: SConscript,v 1.18 2009/05/26 03:31:13 glastrm Exp $
# Authors: James Peachey <James.Peachey-1@nasa.gov>
# Version: pulsePhase-08-05-00

Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('pulsePhaseLib', depsOnly = 1)
pulsePhaseLib = libEnv.StaticLibrary('pulsePhase', listFiles(['src/*.cxx']))

progEnv.Tool('pulsePhaseLib')
gtophaseBin = progEnv.Program('gtophase', listFiles(['src/gtophase/*.cxx']))
gtpphaseBin = progEnv.Program('gtpphase', listFiles(['src/gtpphase/*.cxx']))
test_pulsePhaseBin = progEnv.Program('test_pulsePhase', listFiles(['src/test/*.cxx']))

progEnv.Tool('registerObjects', package = 'pulsePhase', libraries = [pulsePhaseLib], binaries = [gtophaseBin, gtpphaseBin],
             testApps = [test_pulsePhaseBin], includes = listFiles(['pulsePhase/*.h']), pfiles = listFiles(['pfiles/*.par']),
             data = listFiles(['data/*'], recursive = True))
