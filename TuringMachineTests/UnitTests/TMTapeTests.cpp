#include "TMTape.h"
#include "TMExceptions.h"
#include "TMHeadMoveType.h"
#include <memory>

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
using namespace std;

struct TMTapeTestFixtureFor1Arg {
    unique_ptr<TMTape> tape;
    shared_ptr<TMAlphabet> alpha;
    void makeNewTapeWithLength(size_t len) {
        alpha = make_shared<TMAlphabet>("#");
        tape = make_unique<TMTape>(len, alpha);
    }
};

BOOST_FIXTURE_TEST_SUITE( tape_wo_setting_position, TMTapeTestFixtureFor1Arg )

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_0_long_tape ) {
    BOOST_CHECK_THROW(makeNewTapeWithLength(0), ZeroLongTape);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_1_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(1));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 1/2u);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_11_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(11));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 11/2u);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_111_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(111));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 111/2u);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_1001_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(1001));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 1001/2u);
}

BOOST_AUTO_TEST_CASE( setting_head_position_at_0_after_construction_wo_specified_pos_for_1001_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(1001));
    BOOST_REQUIRE_NO_THROW(tape->setHeadPosition(0));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 0u);
}

BOOST_AUTO_TEST_CASE( setting_head_position_at_500_after_construction_wo_specified_pos_for_1001_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(1001));
    BOOST_REQUIRE_NO_THROW(tape->setHeadPosition(500));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 500u);
}

BOOST_AUTO_TEST_CASE( setting_head_position_at_1000_after_construction_wo_specified_pos_for_1001_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(1001));
    BOOST_REQUIRE_NO_THROW(tape->setHeadPosition(1000));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 1000u);
}

BOOST_AUTO_TEST_CASE( setting_head_position_at_1001_after_construction_wo_specified_pos_for_1001_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(1001));
    BOOST_REQUIRE_THROW(tape->setHeadPosition(1001), HeadOutOfTape);
    // set unsuccessful, so head should be still at the middle
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 1001/2u);
}

BOOST_AUTO_TEST_CASE( setting_head_position_at_1050_after_construction_wo_specified_pos_for_1001_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(1001));
    BOOST_REQUIRE_THROW(tape->setHeadPosition(1050), HeadOutOfTape);
    // set unsuccessful, so head should be still at the middle
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 1001/2u);
}

BOOST_AUTO_TEST_CASE( filling_tape_with_hashes_during_construction_wo_specified_pos_for_1001_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(1001));
    BOOST_CHECK_EQUAL((*tape)[0], '#');
    BOOST_CHECK_EQUAL((*tape)[720], '#');
    BOOST_CHECK_EQUAL((*tape)[1000], '#');
}

BOOST_AUTO_TEST_SUITE_END()

struct TMTapeTestFixtureFor2Args {
    shared_ptr<TMTape> tape;
    shared_ptr<TMAlphabet> alpha;
    void makeNewTapeWithLengthAndHeadAt(size_t len, size_t pos) {
        alpha = make_shared<TMAlphabet>("#");
        tape = make_shared<TMTape>(len, alpha);
        tape->setHeadPosition(pos);
    }
};
BOOST_FIXTURE_TEST_SUITE( tape_with_setting_position, TMTapeTestFixtureFor2Args )

BOOST_AUTO_TEST_CASE( head_position_after_construction_for_0_long_tape_with_head_at_0 ) {
    BOOST_CHECK_THROW(makeNewTapeWithLengthAndHeadAt(0, 0), ZeroLongTape);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_for_0_long_tape_with_head_at_1 ) {
    BOOST_CHECK_THROW(makeNewTapeWithLengthAndHeadAt(0, 1), ZeroLongTape);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_for_1_long_tape_with_head_at_1 ) {
    BOOST_CHECK_THROW(makeNewTapeWithLengthAndHeadAt(1, 1), HeadOutOfTape);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_for_1_long_tape_with_head_at_0 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1, 0));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 0u);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_for_5_long_tape_with_head_at_0 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(5, 0));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 0u);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_for_5_long_tape_with_head_at_3 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(5, 3));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 3u);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_for_5_long_tape_with_head_at_4 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(5, 4));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 4u);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_for_1001_long_tape_with_head_at_0 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1001, 0));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 0u);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_for_1001_long_tape_with_head_at_720 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1001, 720));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 720u);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_for_1001_long_tape_with_head_at_1000 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1001, 1000));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 1000u);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_for_1001_long_tape_with_head_at_1001 ) {
    BOOST_CHECK_THROW(makeNewTapeWithLengthAndHeadAt(1001, 1001), HeadOutOfTape);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_for_1001_long_tape_with_head_at_1010 ) {
    BOOST_CHECK_THROW(makeNewTapeWithLengthAndHeadAt(1001, 1010), HeadOutOfTape);
}

BOOST_AUTO_TEST_CASE( setting_head_position_at_0_after_construction_for_1001_long_tape_with_head_at_1000 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1001, 1000));
    BOOST_REQUIRE_NO_THROW(tape->setHeadPosition(0));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 0u);
}

BOOST_AUTO_TEST_CASE( setting_head_position_at_720_after_construction_for_1001_long_tape_with_head_at_1000 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1001, 1000));
    BOOST_REQUIRE_NO_THROW(tape->setHeadPosition(720));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 720u);
}

BOOST_AUTO_TEST_CASE( setting_head_position_at_1000_after_construction_for_1001_long_tape_with_head_at_900 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1001, 900));
    BOOST_REQUIRE_NO_THROW(tape->setHeadPosition(1000));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 1000u);
}

BOOST_AUTO_TEST_CASE( setting_head_position_at_1001_after_construction_for_1001_long_tape_with_head_at_900 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1001, 900));
    BOOST_REQUIRE_THROW(tape->setHeadPosition(1001), HeadOutOfTape);
    // set unsuccessful, so head should be still at the same position
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 900u);
}

BOOST_AUTO_TEST_CASE( setting_head_position_at_1050_after_construction_for_1001_long_tape_with_head_at_900 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1001, 900));
    BOOST_REQUIRE_THROW(tape->setHeadPosition(1050), HeadOutOfTape);
    // set unsuccessful, so head should be still at the same position
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 900u);
}

BOOST_AUTO_TEST_CASE( filling_tape_with_hashes_during_construction_for_1001_long_tape_with_head_at_900 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1001, 900));
    BOOST_CHECK_EQUAL((*tape)[0], '#');
    BOOST_CHECK_EQUAL((*tape)[720], '#');
    BOOST_CHECK_EQUAL((*tape)[1000], '#');
}

BOOST_AUTO_TEST_SUITE_END()

struct TMTapeTestFixtureFor1001LongTapeAndHeadAt500 {
    TMTapeTestFixtureFor1001LongTapeAndHeadAt500() {
        alpha = make_shared<TMAlphabet>("#$01");
        tape = make_shared<TMTape>(len, alpha);
        tape->setHeadPosition(startPos);
    }
    shared_ptr<TMTape> tape;
    shared_ptr<TMAlphabet> alpha;
    size_t len = 1001, startPos = 500;
};
BOOST_FIXTURE_TEST_SUITE( tape_1001LongWithHeadAt500, TMTapeTestFixtureFor1001LongTapeAndHeadAt500 )

BOOST_AUTO_TEST_CASE( charUnderHead_check_if_points_to_correct_element ) {
    BOOST_CHECK_EQUAL( tape->getCharUnderHead(), (*tape)[startPos] );
}

BOOST_AUTO_TEST_CASE( doCmd_with_both_chars_belong_to_alphabet_and_BEFORE_matching_with_tape_move_head_right ) {
    BOOST_REQUIRE_NO_THROW(tape->doCmd('#', '1', TMHeadMoveType::RIGHT));
    BOOST_CHECK_EQUAL((*tape)[startPos], '1'); // state after command
    BOOST_CHECK_EQUAL((*tape)[startPos+1], '#'); // check if next el didn't modified
    BOOST_CHECK_EQUAL((*tape)[startPos-1], '#'); // check if prev el didn't modified
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), startPos+1); // after move right
}

BOOST_AUTO_TEST_CASE( doCmd_with_both_chars_belong_to_alphabet_and_BEFORE_matching_with_tape_move_head_left ) {
    BOOST_REQUIRE_NO_THROW(tape->doCmd('#', '1', TMHeadMoveType::LEFT));
    BOOST_CHECK_EQUAL((*tape)[startPos], '1'); // state after command
    BOOST_CHECK_EQUAL((*tape)[startPos+1], '#'); // check if next el didn't modified
    BOOST_CHECK_EQUAL((*tape)[startPos-1], '#'); // check if prev el didn't modified
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), startPos-1); // after move left
}

BOOST_AUTO_TEST_CASE( doCmd_with_both_chars_belong_to_alphabet_but_mismatch_BEFORE_and_on_tape_state_move_head_right ) {
    BOOST_REQUIRE_THROW(tape->doCmd('$', '1', TMHeadMoveType::RIGHT), MismatchCommandAndElementUnderHead);
    BOOST_CHECK_EQUAL((*tape)[startPos], '#'); // state after command
    BOOST_CHECK_EQUAL((*tape)[startPos+1], '#'); // check if next el didn't modified
    BOOST_CHECK_EQUAL((*tape)[startPos-1], '#'); // check if prev el didn't modified
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), startPos); // after unsuccessful cmd
}

BOOST_AUTO_TEST_CASE( doCmd_with_BEFORE_not_belong_to_alphabet_move_head_right ) {
    BOOST_REQUIRE_THROW(tape->doCmd('m', '1', TMHeadMoveType::RIGHT), CharacterOutOfAlphabet);
    BOOST_CHECK_EQUAL((*tape)[startPos], '#'); // state after command
    BOOST_CHECK_EQUAL((*tape)[startPos+1], '#'); // check if next el didn't modified
    BOOST_CHECK_EQUAL((*tape)[startPos-1], '#'); // check if prev el didn't modified
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), startPos); // after unsuccessful cmd
}

BOOST_AUTO_TEST_CASE( doCmd_with_AFTER_not_belong_to_alphabet_and_BEFORE_matching_with_char_on_tape_move_head_right ) {
    BOOST_REQUIRE_THROW(tape->doCmd('#', 'm', TMHeadMoveType::RIGHT), CharacterOutOfAlphabet);
    BOOST_CHECK_EQUAL((*tape)[startPos], '#'); // state after command
    BOOST_CHECK_EQUAL((*tape)[startPos+1], '#'); // check if next el didn't modified
    BOOST_CHECK_EQUAL((*tape)[startPos-1], '#'); // check if prev el didn't modified
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), startPos); // after unsuccessful cmd
}

BOOST_AUTO_TEST_CASE( doCmd_with_BEFORE_and_AFTER_not_belong_to_alphabet_move_head_right ) {
    BOOST_REQUIRE_THROW(tape->doCmd('z', 'm', TMHeadMoveType::RIGHT), CharacterOutOfAlphabet);
    BOOST_CHECK_EQUAL((*tape)[startPos], '#'); // state after command
    BOOST_CHECK_EQUAL((*tape)[startPos+1], '#'); // check if next el didn't modified
    BOOST_CHECK_EQUAL((*tape)[startPos-1], '#'); // check if prev el didn't modified
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), startPos); // after unsuccessful cmd
}

BOOST_AUTO_TEST_CASE( resetting_the_tape ) {
    BOOST_REQUIRE_NO_THROW(tape->doCmd('#', '1', TMHeadMoveType::RIGHT));
    BOOST_CHECK_EQUAL((*tape)[startPos], '1');
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), startPos+1);
    tape->reset();
    BOOST_CHECK_EQUAL((*tape)[startPos], '#');
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), startPos);
}

BOOST_AUTO_TEST_SUITE_END()
