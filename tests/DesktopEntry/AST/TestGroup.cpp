#include <gtest/gtest.h>

#include <Entry.h>
#include <Comment.h>
#include <Group.h>

using namespace XdgUtils::DesktopEntry::AST;


TEST(TestGroup, create) {
    Group g1("[Desktop Entry]", "Desktop Entry");;
    ASSERT_EQ(g1.getValue(), "Desktop Entry");

    std::vector<std::shared_ptr<Node>> entries1;
    entries1.emplace_back(new Entry(" Name", "Name", "", "", "=My App", "My App"));
    entries1.emplace_back(new Comment("# Test", " Test"));

    g1.setEntries(entries1);

    ASSERT_EQ(g1.getEntries(), entries1);
}

TEST(TestGroup, compare) {
    Group g1("[Desktop Entry]", "Desktop Entry");;

    std::vector<std::shared_ptr<Node>> entries1;
    entries1.emplace_back(new Entry(" Name", "Name", "", "", "=My App", "My App"));
    entries1.emplace_back(new Comment("# Test", " Test"));
    g1.setEntries(entries1);

    Group g2("[Desktop Entry]", "Desktop Entry");;

    std::vector<std::shared_ptr<Node>> entries2;
    entries2.emplace_back(new Entry(" Name", "Name", "", "", "=My App", "My App"));
    entries2.emplace_back(new Comment("# Test", " Test"));
    g2.setEntries(entries2);

    ASSERT_EQ(g1, g2);

    entries1.emplace_back(new Comment("# Test", " Test"));
    g1.setEntries(entries1);

    ASSERT_NE(g1, g2);
}

TEST(TestGroup, write) {
    Group g1("[Desktop Entry]", "Desktop Entry");;

    std::vector<std::shared_ptr<Node>> entries1;
    entries1.emplace_back(new Entry(" Name", "Name", "", "", "=My App", "My App"));
    entries1.emplace_back(new Comment("# Test", " Test"));
    g1.setEntries(entries1);

    std::stringstream res;
    g1.write(res);

    ASSERT_EQ(res.str(), "[Desktop Entry]\n Name=My App\n# Test");
}