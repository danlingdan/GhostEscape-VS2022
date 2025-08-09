#pragma once

#include "../object_affiliate.h"

class TextLabel :public ObjectAffiliate
{
protected:
	TTF_Text* ttf_text_ = nullptr;
	std::string font_path_;
	int font_size_ = 16;

public:
	static TextLabel* addTextLabelChild(ObjectScreen* parent, const std::string& text, const std::string& font_path, int font_size, Anchor anchor = Anchor::CENTER);

	virtual void render() override;
	virtual void clean() override;

	//game_.CreatTTFText("", font_path_, font_size_);
	// getter and settrt
	auto getText() const { return ttf_text_->text; }
	void setFont(const std::string& font_path, int font_size);
	auto getFontPath() const { return font_path_; }
	void setFontPath(const std::string& font_path);
	auto getFontSize() const { return font_size_; }
	void setFontSize(int font_size);
	void setText(std::string ttf_text) { TTF_SetTextString(ttf_text_, ttf_text.c_str(), 0); }

private:
	void updateSize(); // change size by the text
};
