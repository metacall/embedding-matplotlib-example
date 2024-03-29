#
#	MetaCall Embedding Matplotlib Example by Parra Studios
#	An example of embedding matplotlib from Python into C/C++.
#
#	Copyright (C) 2016 - 2020 Vicente Eduardo Ferrer Garcia <vic798@gmail.com>
#
#	Licensed under the Apache License, Version 2.0 (the "License");
#	you may not use this file except in compliance with the License.
#	You may obtain a copy of the License at
#
#		http://www.apache.org/licenses/LICENSE-2.0
#
#	Unless required by applicable law or agreed to in writing, software
#	distributed under the License is distributed on an "AS IS" BASIS,
#	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#	See the License for the specific language governing permissions and
#	limitations under the License.
#

FROM debian:bullseye-slim

# Image descriptor
LABEL copyright.name="Vicente Eduardo Ferrer Garcia" \
	copyright.address="vic798@gmail.com" \
	maintainer.name="Vicente Eduardo Ferrer Garcia" \
	maintainer.address="vic798@gmail.com" \
	vendor="MetaCall Inc." \
	version="0.1"

# Install dependencies
RUN apt-get update \
	&& apt-get install -y --no-install-recommends build-essential cmake ca-certificates git python3-dev python3-pip

# Clone and build MetaCall
RUN git clone --depth=1 --branch v0.7.3 https://github.com/metacall/core.git \
	&& mkdir core/build && cd core/build \
	&& cmake -DOPTION_BUILD_LOADERS_PY=On -DOPTION_BUILD_DETOURS=Off -DOPTION_BUILD_SCRIPTS=Off -DOPTION_BUILD_TESTS=Off .. \
	&& cmake --build . --target install \
	&& ldconfig

# Install matplotlib
RUN pip3 install --user matplotlib

# Copy sources
COPY main.c plot.py ./

# Build and run the executable
RUN export LOADER_SCRIPT_PATH="`pwd`" \
	&& mkdir output \
	&& gcc \
		-std=c11 \
		main.c \
		-lmetacall \
	&& ./a.out
