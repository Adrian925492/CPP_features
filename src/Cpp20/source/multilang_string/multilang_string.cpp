#include "multilang_string.hpp"

#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

namespace multilangStrings {

using stringId = uint32_t;  //Type of string "key" id

//Defines available languages
enum class Languages
{
    EN_US,
    PL,
    Undefined
};

class CsvStringManager
{
public:
    CsvStringManager() = default;

    std::string getString(stringId id)
    {
        std::string text;

        const auto lang_filepath = paths.find(lang);
        if (paths.end() == lang_filepath)
            throw std::filesystem::filesystem_error("Language not supported!", std::error_code());

        const auto filePath = std::filesystem::path(__FILE__).parent_path() / std::filesystem::path(lang_filepath->second);

        if (not std::filesystem::exists(filePath))
            throw std::filesystem::filesystem_error("Language file not found!", std::error_code());
        
        if (std::ifstream csv_file(filePath); csv_file) {
            std::string line;
            
            while(std::getline(csv_file, line)) {
                if (line.size() > 0) {
                    std::stringstream lineStream(line);
                    std::string record;

                    std::getline(lineStream, record, delimiter);
                    std::stringstream idStream(record);
                    stringId _id;
                    idStream >> _id;

                    if (_id == id) {
                        std::getline(lineStream, text, delimiter);
                        return text;
                    }
                }
            }
        } else {
            throw std::filesystem::filesystem_error("File cannot be opened!", std::error_code());
        }
        return text;
    }

    void setLanguage(Languages _lang)
    {
        lang = _lang;
    }
private:
    Languages lang;
    constexpr static char delimiter{','};

    const std::unordered_map<Languages, std::string> paths {
        {Languages::EN_US, "./en_us.csv"},
        {Languages::PL, "./pl.csv"}
    };

};

};
void multilang_string_main()
{
    std::cout << "-------- Multilang string --------\n";

    multilangStrings::CsvStringManager str;
    str.setLanguage(multilangStrings::Languages::EN_US);

    std::cout << "English (US) language words:\t" << str.getString(1) << ",\t" << str.getString(2) << "\n";

    str.setLanguage(multilangStrings::Languages::PL);
    std::cout << "Polish language words:\t" << str.getString(1) << ",\t" << str.getString(2) << "\n";
}