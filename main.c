/*
 *	MetaCall Embedding Matplotlib Example by Parra Studios
 *	An example of embedding matplotlib from Python into C/C++.
 *
 *	Copyright (C) 2016 - 2020 Vicente Eduardo Ferrer Garcia <vic798@gmail.com>
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 */

#include <metacall/metacall.h>
#include <stdio.h>

#define metacall_value_create_str(str) \
	metacall_value_create_string(str, sizeof(str) - 1)

static int cleanup(int code)
{
	if (metacall_destroy() != 0)
	{
		return code != 0 ? -code : -255;
	}

	return code;
}

int main(int argc, char *argv[])
{
	struct metacall_log_stdio_type log_stdio = { stdout };

	printf(metacall_print_info());

	// Define log stream
	if (metacall_log(METACALL_LOG_STDIO, (void *)&log_stdio) != 0)
	{
		return cleanup(1);
	}

	// Initialize MetaCall
	if (metacall_initialize() != 0)
	{
		return cleanup(2);
	}

	// Python
	{
		// Array of scripts to be loaded by MetaCall
		const char * py_scripts[] =
		{
			"plot.py"
		};

		const void * array_x[] = { metacall_value_create_int(1), metacall_value_create_int(2) };
		const void * array_y[] = { metacall_value_create_int(3), metacall_value_create_int(4) };

		// Parameters to be passed to the plot function
		void * args[] =
		{
			metacall_value_create_str("Hello World"), // title
			metacall_value_create_array(array_x, sizeof(array_x) / sizeof(array_x[0])), // x
			metacall_value_create_array(array_y, sizeof(array_y) / sizeof(array_y[0])), // y
			metacall_value_create_str("X"), // xlabel
			metacall_value_create_str("Y"), // ylabel
			metacall_value_create_str("plot.png") // output
		};

		void * ret = NULL;

		// Load scripts
		if (metacall_load_from_file("py", py_scripts, sizeof(py_scripts) / sizeof(py_scripts[0]), NULL) != 0)
		{
			return cleanup(3);
		}

		// Call to plot function
		ret = metacallv("plot", args);

		// Clean up arguments
		for (size_t it = 0; it < sizeof(args) / sizeof(args[0]); ++it)
		{
			metacall_value_destroy(args[it]);
		}

		if (ret == NULL)
		{
			return cleanup(4);
		}

		// Clean up return value
		metacall_value_destroy(ret);
	}

	return cleanup(0);
}
