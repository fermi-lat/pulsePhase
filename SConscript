# -*- python -*-
# $Id: SConscript,v 1.26 2010/03/16 21:53:22 hirayama Exp $
# Authors: James Peachey <James.Peachey-1@nasa.gov>
# Version: pulsePhase-08-06-04

Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

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
