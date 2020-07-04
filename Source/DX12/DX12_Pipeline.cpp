#include "DX12_Pipeline.hpp"

#include <fstream>
#include <iostream>

#include "../Json.hpp"

using namespace nlohmann;

/** Default Constructor */
DX12_Pipeline::DX12_Pipeline()
{

}

/** Internal Constructor */
DX12_Pipeline::DX12_Pipeline(
    RenderDevice* renderDev,
    const std::string pipelinePath)
{

    std::ifstream pipelineFile(pipelinePath.c_str());

    json pipelineFileJson; 
    pipelineFile >> pipelineFileJson;

    json elems = pipelineFileJson["Elements"];

    for(auto elem : elems) // Get an element from the elems array
        for(auto iter = elem.begin(); iter != elem.end(); ++iter) // Get the name of the object and its value
            Elements.push_back(std::pair<std::string, std::string>(iter.key(), iter.value())); // Add the json object to a C++ array for the elements the shaders have

    // Load shaders from the file
    if(!SUCCEEDED(D3DCompileFromFile()))

    // Create the vertex input layout

    

}

/** Default Destructor */
DX12_Pipeline::~DX12_Pipeline()
{

}