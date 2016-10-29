#include "TextQuery.h"
#include <sstream>

void TextQuery::
store_file(std::ifstream &is){
	std::string textline;
	while(getline(is, textline)) // !!!
		lines_of_text.push_back(textline);
}

void TextQuery::
build_map(){
	for(line_no line_num = 0;
			line_num != lines_of_text.size();
			++line_num){
		std::istringstream line(lines_of_text[line_num]);
		std::string word;
		while(line >> word)
			word_map[word].insert(line_num);
	}
}

std::set<TextQuery::line_no> TextQuery::
run_query(const std::string &query_word) const{
	std::map<std::string, std::set<line_no> >::const_iterator
		loc = word_map.find(query_word);
	if(loc == word_map.end())
		return std::set<line_no>();
	else
		return loc->second;
}

std::string TextQuery::
text_line(line_no line) const{
	if(line < lines_of_text.size())
		return lines_of_text[line];
	//throw std::out_of_range("line number out of range");
}
