# -*- python -*-
# $Id: SConscript,v 1.21 2009/07/15 18:33:23 glastrm Exp $
# Authors: James Peachey <James.Peachey-1@nasa.gov>
# Version: pulsePhase-08-06-00

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

progEnv.Tool('registerTargets', package = 'pulsePhase',
             staticLibraryCxts = [[pulsePhaseLib, progEnv]],
             binaryCxts = [[gtophaseBin,progEnv], [gtpphaseBin, progEnv]],
             testAppCxts = [[test_pulsePhaseBin, progEnv]],
             includes = listFiles(['pulsePhase/*.h']),
             pfiles = listFiles(['pfiles/*.par']),
             data = listFiles(['data/*'], recursive = True))
