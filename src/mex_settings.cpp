#include "mex_settings.h"
#include <fstream>

// enums names
static const CharString sMdlFormatNames[] = {
    "Obj",
    "Fbx"
};
static const CharString sTexFormatNames[] = {
    "Dds",
    "LegacyDds",
    "Tga",
    "Png"
};
static const CharString sSndFormatNames[] = {
    "Ogg",
    "Wav"
};

template <typename T, size_t N>
static T NameToEnum(const CharString& name, const CharString (&enumNames)[N]) {
    T result = scast<T>(0);

    size_t i = 0;
    for (const CharString& n : enumNames) {
        if (n == name) {
            result = scast<T>(i);
            break;
        }
        ++i;
    }

    return result;
}


MEXSettings::MEXSettings() {

}
MEXSettings::~MEXSettings() {

}

void MEXSettings::SetFolder(const fs::path& folder) {
    mFolder = folder;
}

bool MEXSettings::Load() {
    bool result = false;

    fs::path path = mFolder / L"settings.mex";

    std::ifstream file(path);
    if (file.good()) {
        pugi::xml_document doc;
        const uint32_t options = pugi::parse_pi | pugi::parse_default;
        pugi::xml_parse_result parseResult = doc.load(file, options);
        if (parseResult) {
            pugi::xml_node decl = doc.child("MetroEX-document");
            if (decl && decl.value() == CharString(R"(type="Settings")")) {
                result = this->LoadExtraction(doc);
            }
        }
    }

    return result;
}

bool MEXSettings::Save() {
    fs::path path = mFolder / L"settings.mex";

    pugi::xml_document doc;
    // add a custom declaration nodes
    // <?xml version="1.0" encoding="UTF-8"?>
    pugi::xml_node xmlDecl = doc.append_child(pugi::node_declaration);
    xmlDecl.set_name("xml");
    xmlDecl.append_attribute("version") = "1.0";
    xmlDecl.append_attribute("encoding") = "UTF-8";
    // <?MetroEX-document type="Settings"?>
    pugi::xml_node excelDecl = doc.append_child(pugi::node_declaration);
    excelDecl.set_name("MetroEX-document");
    excelDecl.append_attribute("type") = "Settings";

    this->SaveExtraction(doc);

    return doc.save_file(path.native().c_str(), "  ", pugi::format_default, pugi::encoding_utf8);
}


void MEXSettings::InitDefaults() {
    //// extraction
    // models
    this->extraction.modelFormat = Extraction::MdlFormat::Obj;
    this->extraction.modelSaveWithAnims = true;
    this->extraction.modelAnimsSeparate = false;
    // textures
    this->extraction.textureFormat = Extraction::TexFormat::Tga;
    // sounds
    this->extraction.soundFormat = Extraction::SndFormat::Ogg;
    //stuff
    this->extraction.askEveryTime = false;
}

// loading
bool MEXSettings::LoadExtraction(pugi::xml_document& doc) {
    bool result = false;

    pugi::xml_node extractionNode = doc.child("Extraction");
    if (extractionNode) {
        // models
        this->extraction.modelFormat = NameToEnum<Extraction::MdlFormat>(extractionNode.child("modelFormat").text().get(), sMdlFormatNames);
        this->extraction.modelSaveWithAnims = extractionNode.child("modelSaveWithAnims").text().get() == CharString("true");
        this->extraction.modelAnimsSeparate = extractionNode.child("modelAnimsSeparate").text().get() == CharString("true");

        // textures
        this->extraction.textureFormat = NameToEnum<Extraction::TexFormat>(extractionNode.child("textureFormat").text().get(), sTexFormatNames);

        // sounds
        this->extraction.soundFormat = NameToEnum<Extraction::SndFormat>(extractionNode.child("soundFormat").text().get(), sSndFormatNames);

        //stuff
        this->extraction.askEveryTime = extractionNode.child("askEveryTime").text().get() == CharString("true");

        result = true;
    }

    return result;
}

// saving
bool MEXSettings::SaveExtraction(pugi::xml_document& doc) {
    pugi::xml_node extractionNode = doc.append_child("Extraction");

    // models
    extractionNode.append_child("modelFormat").text() = sMdlFormatNames[scast<size_t>(this->extraction.modelFormat)].c_str();
    extractionNode.append_child("modelSaveWithAnims").text() = this->extraction.modelSaveWithAnims ? "true" : "false";
    extractionNode.append_child("modelAnimsSeparate").text() = this->extraction.modelAnimsSeparate ? "true" : "false";

    // textures
    extractionNode.append_child("textureFormat").text() = sTexFormatNames[scast<size_t>(this->extraction.textureFormat)].c_str();

    // sounds
    extractionNode.append_child("soundFormat").text() = sSndFormatNames[scast<size_t>(this->extraction.soundFormat)].c_str();

    //stuff
    extractionNode.append_child("askEveryTime").text() = this->extraction.askEveryTime ? "true" : "false";

    return true;
}