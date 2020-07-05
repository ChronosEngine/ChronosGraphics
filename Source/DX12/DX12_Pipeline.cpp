#include "DX12_Pipeline.hpp"

#include <fstream>
#include <iostream>

#include "DX12_RenderDevice.hpp"
#include "../Json.hpp"
#include "../Log.hpp"

using namespace nlohmann;

LPCWSTR 
strToLPCWSTR(
    const std::string& s);

/** Default Constructor */
DX12_Pipeline::DX12_Pipeline()
{

}

/** Internal Constructor */
DX12_Pipeline::DX12_Pipeline(
    RenderDevice* renderDev,
    const std::string pipelinePath)
{
    renderDevice = static_cast<DX12_RenderDevice*>(renderDev);

    std::ifstream pipelineFile(pipelinePath.c_str());

    json pipelineFileJson; 
    pipelineFile >> pipelineFileJson;

    json elems = pipelineFileJson["Elements"];

    for(auto elem : elems) // Get an element from the elems array
        for(auto iter = elem.begin(); iter != elem.end(); ++iter) // Get the name of the object and its value
            Elements.push_back(std::pair<std::string, std::string>(iter.key(), iter.value())); // Add the json object to a C++ array for the elements the shaders have

    // Get the path of the .pipeline file
    size_t pipelinePathLocation = pipelinePath.find_last_of("\\/");
    std::string pipelineFilePath = pipelinePath.substr(0, pipelinePathLocation);
    pipelineFilePath.append("/");

    // Get the shaders paths
    std::string hlslPath = pipelineFilePath + pipelineFileJson["Files"]["Vertex"]["HLSL"].get<std::string>();
    
#ifdef _DEBUG
    UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
    UINT compileFlags = 0;
#endif


    LPCWSTR str = strToLPCWSTR(hlslPath);

    std::cout << str << std::endl;

    

    // Create the vertex input layout

    

}

/** Default Destructor */
DX12_Pipeline::~DX12_Pipeline()
{

}

// HELPERS //

// https://stackoverflow.com/a/27296
LPCWSTR 
strToLPCWSTR(
    const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r.c_str();
}