PARTICLE_PLATFORM=photon
VERSION=0.6.3

all: ${PARTICLE_PLATFORM}.bin

${PARTICLE_PLATFORM}.bin: examples/usage/usage.ino src/ModbusMaster-Particle.*
	particle compile ${PARTICLE_PLATFORM} $< --saveTo ${PARTICLE_PLATFORM}.bin --target ${VERSION}
