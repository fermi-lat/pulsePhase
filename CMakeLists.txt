##### Library ######
add_library(pulsePhase src/OrbitalPhaseApp.cxx src/PulsePhaseApp.cxx)
target_link_libraries(pulsePhase PUBLIC pulsarDb st_app st_facilities timeSystem tip)
target_include_directories(
  pulsePhase PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src
  $<INSTALL_INTERFACE:>/src
)

###### Executables ######
add_executable(gtophase src/gtophase/gtophase.cxx)
add_executable(gtpphase src/gtpphase/gtpphase.cxx)

target_link_libraries(gtophase PRIVATE pulsePhase)
target_link_libraries(gtpphase PRIVATE pulsePhase)

###### Tests ######
add_executable(test_pulsePhase src/test/test_pulsePhase.cxx)
target_link_libraries(test_pulsePhase PRIVATE pulsePhase)


###############################################################
# Installation
###############################################################
install(DIRECTORY pfiles/ DESTINATION ${FERMI_INSTALL_PFILESDIR})
install(DIRECTORY data/outref DESTINATION ${FERMI_INSTALL_DATADIR}/pulsePhase)
install(DIRECTORY data/ DESTINATION ${FERMI_INSTALL_REFDATADIR}/pulsePhase)

install(
  TARGETS pulsePhase gtophase gtpphase test_pulsePhase
  EXPORT fermiTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
