/**
 * Unit Tests for GoalUndo class
**/

#include <gtest/gtest.h>
#include "GoalUndo.h"
using namespace std;

class GoalUndoTest : public ::testing::Test
{
	protected:
		GoalUndoTest(){}
		virtual ~GoalUndoTest(){}
		virtual void SetUp(){}
		virtual void TearDown(){}
};

TEST(GoalUndoTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(GoalUndoTest, testGetGoalNoGoal)
{
  GoalUndo g;
  ASSERT_TRUE(g.getGoal() == "");
}

TEST(GoalUndoTest, testGetGoalWithGoal)
{
  GoalUndo g;
  string goalName = "Get an 'A'";
  g.addOperation(goalName,"Write unit test");
  ASSERT_TRUE(g.getGoal() == goalName);
}

TEST(GoalUndoTest, testGetGoalAfterUndoSingleOperation)
{
  GoalUndo g;
  string goalName = "Get an 'A'";
  g.addOperation(goalName,"Write buggy unit test");
  g.undoOperation();
  ASSERT_TRUE(g.getGoal() == "");
}

TEST(GoalUndoTest, testGetGoalAfterUndoSingleOperationAlt)
{
  GoalUndo g;
  string goalName = "Get an 'A'";
  g.addOperation(goalName,"Fork repo");
  g.addOperation(goalName,"Write buggy unit test");
  g.undoOperation();
  ASSERT_TRUE(g.getGoal() != "");
}

TEST(GoalUndoTest, testGetGoalAfterUnitOpGoalUndo)
{
  GoalUndo g;
  string goalName = "Get an 'A'";
  g.addOperation(goalName, "Write buggy unit test");
  g.undoGoal();
  ASSERT_TRUE(g.getGoal() == "");
}

TEST(GoalUndoTest, testGetGoalAfterMultiOpGoalUndo)
{
  GoalUndo g;
  string goalName = "Get an 'A'";
  g.addOperation(goalName,"Fork repo");
  g.addOperation("Write unit test");
  g.undoGoal();
  ASSERT_TRUE(g.getGoal() == "");
}

TEST(GoalUndoTest, testGetGoalAfterMultiOpGoalUndoAlt)
{
  GoalUndo g;
  string goalName = "Get an 'A'";
  g.addOperation(goalName,"Fork repo");
  g.addOperation("Write unit test");
  string altGoalName = "Start summer";
  g.addOperation(altGoalName,"Chill out");
  g.undoGoal();
  ASSERT_TRUE(g.getGoal() == goalName);
}

TEST(GoalUndoTest, testDefaultGoalNaming)
{
  GoalUndo g;
  g.addOperation("do something");
  ASSERT_TRUE(g.getGoal() == "do something");
}

TEST(GoalUndoTest, testEmptyStringDefaultGoalNaming)
{
  GoalUndo g;
  g.addOperation("");
  ASSERT_TRUE(g.getGoal() == "");
}

TEST(GoalUndoTest, testNoOpUndo)
{
  GoalUndo g;
  g.undoOperation();
  ASSERT_TRUE(g.getGoal() == "");
}

TEST(GoalUndoTest, testNoGoalUndo)
{
  GoalUndo g;
  g.undoGoal();
  ASSERT_TRUE(g.getGoal() == "");
}

TEST(GoalUndoTest, testGetOpsNoGoal)
{
  GoalUndo g;
  ASSERT_TRUE(g.getOperations() == "");
}

TEST(GoalUndoTest, testGetOpsTrickyOps)
{
  GoalUndo g;
  g.addOperation("");
  g.addOperation("");
  ASSERT_TRUE(g.getOperations() == "");
}

TEST(GoalUndoTest, testGetOpsTrickyOpsRedux)
{
  GoalUndo g;
  g.addOperation("\0");
  g.addOperation("\0");
  ASSERT_TRUE(g.getOperations() == "\0 \0");
}

TEST(GoalUndoTest, testGetOpsTrickyOpsTrifecta)
{
  GoalUndo g;
  g.addOperation(" ");
  g.addOperation(" ");
  ASSERT_TRUE(g.getOperations() == "   ");
}

TEST(GoalUndoTest, testGetOpsNormalOps)
{
  GoalUndo g;
  g.addOperation("learn c++");
  g.addOperation("master c++");
  ASSERT_TRUE(g.getOperations() == "learn c++ master c++");
}

TEST(GoalUndoTest, testGetOps)
{
  GoalUndo g;
  g.addOperation("","eat");
  g.addOperation("","sleep");
  g.addOperation("do something else");
  ASSERT_TRUE(g.getOperations() == "do something else");
}

TEST(GoalUndoTest, testGetOpsAlternatingGoal)
{
  GoalUndo g;
  g.addOperation("Pokemon","Gotta catch'em all");
  g.addOperation("Ultimate Goal","Travel the world");
  g.addOperation("Pokemon","Battle every day");
  g.addOperation("Ultimate Goal","Meet people");
  ASSERT_TRUE(g.getOperations() == "Meet people");
  g.undoGoal();
  g.undoGoal();
  ASSERT_TRUE(g.getOperations() == "Travel the world");
}

TEST(GoalUndoTest, testGetOpsDupGoalName)
{
  GoalUndo g;
  g.addOperation("someGoal","1");
  g.addOperation("someGoal","2");
  g.addOperation("someGoal","3");
  g.addOperation("someGoal","4");
  ASSERT_TRUE(g.getOperations() == "4");
}

TEST(GoalUndoTest, testGetOpsProper)
{
  GoalUndo g;
  g.addOperation("someGoal","1");
  g.addOperation("2");
  g.addOperation("3");
  g.addOperation("4");
  ASSERT_TRUE(g.getOperations() == "1 2 3 4");
}

TEST(GoalUndoTest, testExplicitSimpleOpUndo)
{
  GoalUndo g;
  g.addOperation("someGoal","1");
  g.addOperation("2");
  g.addOperation("3");
  g.addOperation("4");
  g.undoOperation("4");
  ASSERT_TRUE(g.getOperations() == "1 2 3");
}

TEST(GoalUndoTest, testExplicitSimpleOutofOrderOpUndo)
{
  GoalUndo g;
  g.addOperation("someGoal","1");
  g.addOperation("2");
  g.addOperation("3");
  g.addOperation("4");
  g.undoOperation("2");
  ASSERT_TRUE(g.getOperations() == "1 3 4");
}

TEST(GoalUndoTest, testExplicitSingleOpGoalUndo)
{
  GoalUndo g;
  g.addOperation("someGoal","pass");
  g.undoOperation("pass");
  ASSERT_TRUE(g.getGoal() == "someGoal");
  ASSERT_TRUE(g.getOperations() == "");
}
