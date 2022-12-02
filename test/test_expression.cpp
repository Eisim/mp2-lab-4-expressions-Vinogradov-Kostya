#include "expression.h"

#include <gtest.h>

TEST(Expression, can_create_empty_expression)
{
  ASSERT_NO_THROW(Expression exp);
}
