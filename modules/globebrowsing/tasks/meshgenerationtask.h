/*****************************************************************************************
*                                                                                       *
* OpenSpace                                                                             *
*                                                                                       *
* Copyright (c) 2014-2017                                                               *
*                                                                                       *
* Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
* software and associated documentation files (the "Software"), to deal in the Software *
* without restriction, including without limitation the rights to use, copy, modify,    *
* merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
* permit persons to whom the Software is furnished to do so, subject to the following   *
* conditions:                                                                           *
*                                                                                       *
* The above copyright notice and this permission notice shall be included in all copies *
* or substantial portions of the Software.                                              *
*                                                                                       *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
* CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
****************************************************************************************/

#ifndef __OPENSPACE___MESH_GENERATION_TASK___H__
#define __OPENSPACE___MESH_GENERATION_TASK___H__

#include <ghoul\misc\dictionary.h>
#include <openspace\util\task.h>

namespace openspace {
namespace globebrowsing {
	class MeshGenerationTask : public Task {
	public:
		struct File {
			std::string filename;
			std::string outputFilename;
		};

		MeshGenerationTask(const ghoul::Dictionary& dictionary);

		std::string description() override;

		void perform(const Task::ProgressCallback& progressCallback) override;

	private :

		std::vector<File> readFilenames(const std::string filename);
		bool downloadBinaryFile(const std::string filename, std::string binary_path);
		std::string MeshGenerationTask::extractOutputFilename(std::string filename);

		std::string _inputTxt;
		std::string _outputPath;
		std::string _inputSol;
		std::string _rootPath;
		std::string _levelOfDetail;
		std::string _pathToModelsFolder;
		std::vector<File> _filenames;

		ghoul::Dictionary _generationParams;
	};
} // namespace globebrowsing
} // namespace openspace

#endif //__GHOUL___MESH_GENERATION_TASK___H__