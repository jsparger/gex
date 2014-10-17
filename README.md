Gex: Geant4 Extensions
====

Tools and adapters for Geant4 users.

This project is being migrated to GitHub from a private repository. Here is the checklist:

- [x] Migrate code
- [x] Create simple simulation example
- [ ] Create companion data readout example
- [ ] Create useful README and Wiki
- [ ] Improve building and linking process
 
If you're here before the wiki but want to try Gex anyway, check out the simple example. To run the example, here are some things you'll need to do:

- Source your geant4.sh and thisroot.sh scripts.
- Build Gex: cd <path_to_gex>; mkdir build; cd build; cmake ..; make;
- Set the environment variable GEX_LIBS=<path_to_gex>/build/libGex.[so/dylib]
- Set the environment variable GEX_INCLUDE_DIR=<path_to_gex>/include
- Build the example: cd <path_to_gex>/examples/simple; mkdir build; cd build; cmake ..; make; ./simple;

To build and run, Gex requires:

- A compiler supporting C++14 such as gcc 4.9.1
- Geant4 10.0 (tested with patch 02)
- Cern Root (tested with v5.34/14)
- CMake



