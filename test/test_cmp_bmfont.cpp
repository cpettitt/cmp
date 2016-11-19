#include <stdio.h>

#define CMP_BMFONT_IMPLEMENTATION
#include "cmp_bmfont.hpp"

using namespace cmp;

#define ASSERT_NULLPTR(actual)                                                                     \
    if (actual != nullptr) {                                                                       \
        printf("%s(%d): failed: expected nullptr, got: %p\n", __FILE__, __LINE__, actual);         \
        fail = true;                                                                               \
    }


#define ASSERT_STR_EQ(expected, actual)                                                            \
    if (actual == nullptr || strcmp(expected, actual)) {                                           \
        printf("%s(%d): failed: expected: '%s', got: '%s'\n",                                      \
               __FILE__,                                                                           \
               __LINE__,                                                                           \
               expected,                                                                           \
               actual);                                                                            \
        fail = true;                                                    \
    }

#define ASSERT_INT_EQ(expected, actual)                                                            \
    if (expected != actual) {                                                                      \
        printf("%s(%d): failed: expected: %d, got: %d\n", __FILE__, __LINE__, expected, actual);   \
        fail = true;                                                                               \
    }

static bool fail = false;

int main() {
    BMFont *font = bmfont_parse_file("../test_data/valid.fnt");
    if (!font) {
        printf("%s: failed: %s\n", __FILE__, bmfont_get_error_string());
        exit(1);
    }

    ASSERT_STR_EQ("valid", font->font_name);
    ASSERT_INT_EQ(8, font->font_size);
    ASSERT_INT_EQ(8, font->line_height);
    ASSERT_INT_EQ(7, font->base);
    ASSERT_INT_EQ(128, font->scale_w);
    ASSERT_INT_EQ(512, font->scale_h);
    ASSERT_INT_EQ(1, font->num_pages);
    ASSERT_STR_EQ("valid.png", font->page_names[0]);
    ASSERT_INT_EQ(3, font->num_chars);
    ASSERT_INT_EQ(33, font->chars[0].id);
    ASSERT_INT_EQ(2, font->chars[0].x);
    ASSERT_INT_EQ(3, font->chars[0].y);
    ASSERT_INT_EQ(6, font->chars[0].width);
    ASSERT_INT_EQ(7, font->chars[0].height);
    ASSERT_INT_EQ(0, font->chars[0].x_offset);
    ASSERT_INT_EQ(1, font->chars[0].y_offset);
    ASSERT_INT_EQ(8, font->chars[0].x_advance);
    ASSERT_INT_EQ(0, font->chars[0].page);
    ASSERT_INT_EQ(2, font->num_kernings);
    ASSERT_INT_EQ(33, font->kernings[0].first);
    ASSERT_INT_EQ(34, font->kernings[0].second);
    ASSERT_INT_EQ(-4, font->kernings[0].amount);

    bmfont_free(font);


    font = bmfont_parse_file("../test_data/valid_no_kernings.fnt");
    if (!font) {
        printf("%s: failed: %s\n", __FILE__, bmfont_get_error_string());
        exit(1);
    }

    ASSERT_STR_EQ("valid", font->font_name);
    ASSERT_INT_EQ(1, font->num_pages);
    ASSERT_STR_EQ("valid.png", font->page_names[0]);
    ASSERT_INT_EQ(3, font->num_chars);
    ASSERT_INT_EQ(0, font->num_kernings);

    bmfont_free(font);


    font = bmfont_parse_file("../test_data/does_not_exist");
    ASSERT_NULLPTR(font);

    font = bmfont_parse_file("../test_data/too_many_chars.fnt");
    ASSERT_NULLPTR(font);

    font = bmfont_parse_file("../test_data/too_few_chars.fnt");
    ASSERT_NULLPTR(font);

    font = bmfont_parse_file("../test_data/too_many_kernings.fnt");
    ASSERT_NULLPTR(font);

    font = bmfont_parse_file("../test_data/too_few_kernings.fnt");
    ASSERT_NULLPTR(font);

    font = bmfont_parse_file("../test_data/too_many_pages.fnt");
    ASSERT_NULLPTR(font);

    font = bmfont_parse_file("../test_data/too_few_pages.fnt");
    ASSERT_NULLPTR(font);

    if (!fail) {
        printf("test_cmp_bmfont: success\n");
        return 0;
    }

    return 1;
}
