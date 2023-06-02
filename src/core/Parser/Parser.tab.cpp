// A Bison parser, made by GNU Bison 3.7.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 1 "Parser.y"
 /*** C/C++ Declarations ***/

#pragma warning(disable : 4996)  // Looks like we need this for it to compile ...

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>

#include "src/core/SDB_core.h"
#include "src/core/Parser/Driver.h"


#line 55 "Parser.tab.cpp"


#include "Parser.tab.h"

// Second part of user prologue.
#line 167 "Parser.y"


#include <memory>
#include "src/core/Parser/Driver.h"
#include "src/core/Parser/Scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex


std::string operator_sequence_string(std::vector<std::string> vec) {
    std::string s;
    for (const auto &s2: vec) {
        s += s2 + ", ";
    }
    return s;
}


#line 84 "Parser.tab.cpp"



#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 34 "Parser.y"
namespace SDB {
#line 178 "Parser.tab.cpp"

  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  Parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  Parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.kind ())
    {
      case symbol_kind::S_STRING: // "string"
#line 160 "Parser.y"
                    { delete (yysym.value.stringVal); }
#line 384 "Parser.tab.cpp"
        break;

      case symbol_kind::S_ket: // ket
#line 161 "Parser.y"
                    { delete (yysym.value.bSeq); }
#line 390 "Parser.tab.cpp"
        break;

      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 46 "Parser.y"
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 533 "Parser.tab.cpp"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 6: // item: operator_or_general_sequence "end of line"
#line 203 "Parser.y"
                                        { driver.result = (yystack_[1].value.opWithSeqVal)->Compile(driver.context); }
#line 671 "Parser.tab.cpp"
    break;

  case 7: // item: learn_rule "end of line"
#line 206 "Parser.y"
                      { /* std::cout << "learn rule: " << $1->to_string() << std::endl; */ (yystack_[1].value.learnRuleVal)->Compile(driver.context); }
#line 677 "Parser.tab.cpp"
    break;

  case 8: // item: general_learn_rule "end of line"
#line 207 "Parser.y"
                              { /* std::cout << "multi learn rule:\n" << $1->to_string() << std::endl; */ (yystack_[1].value.learnRuleVal)->Compile(driver.context); }
#line 683 "Parser.tab.cpp"
    break;

  case 11: // item: "context learn rule" "ket label idx" "end of line"
#line 210 "Parser.y"
                             { driver.context.set(ket_map.get_str((yystack_[1].value.ulongVal))); }
#line 689 "Parser.tab.cpp"
    break;

  case 12: // item: "dollar symbol" "end of line followed by indent" multi_learn_rule "end of line"
#line 211 "Parser.y"
                                              { std::cout << "\n" << (yystack_[1].value.multiLearnRuleVal)->Compile(driver.context).to_string() << "\n"; }
#line 695 "Parser.tab.cpp"
    break;

  case 14: // ket: "ket label idx"
#line 218 "Parser.y"
                  { (yylhs.value.bSeq) = new Ket((yystack_[0].value.ulongVal)); }
#line 701 "Parser.tab.cpp"
    break;

  case 15: // ket: "self ket"
#line 219 "Parser.y"
                 { (yylhs.value.bSeq) = new SelfKet(); }
#line 707 "Parser.tab.cpp"
    break;

  case 16: // ket: "multi self ket"
#line 220 "Parser.y"
                       { (yylhs.value.bSeq) = new MultiSelfKet(); }
#line 713 "Parser.tab.cpp"
    break;

  case 17: // ket: "multi self ket k"
#line 221 "Parser.y"
                        { (yylhs.value.bSeq) = new MultiSelfKet((yystack_[0].value.integerVal)); }
#line 719 "Parser.tab.cpp"
    break;

  case 18: // learn_rule: operator_with_sequence "learn symbol" operator_or_general_sequence
#line 245 "Parser.y"
                                                                           { (yylhs.value.learnRuleVal) = new LearnRule(*(yystack_[2].value.opWithSeqVal), (yystack_[1].value.integerVal), *(yystack_[0].value.opWithSeqVal)); }
#line 725 "Parser.tab.cpp"
    break;

  case 19: // general_learn_rule: operator_with_sequence "learn symbol" "end of line followed by indent" multi_learn_rule
#line 248 "Parser.y"
                                                                                  { (yylhs.value.learnRuleVal) = new LearnRule(*(yystack_[3].value.opWithSeqVal), (yystack_[2].value.integerVal), *(yystack_[0].value.multiLearnRuleVal)); }
#line 731 "Parser.tab.cpp"
    break;

  case 20: // if_else_statement: "open if statement" operator_or_general_sequence "right parenthesis" "colon symbol" "end of line followed by indent" multi_learn_rule "end of line followed by undent" "close statement"
#line 251 "Parser.y"
                                                                                                                   {
                       MultiLearnRule *empty_rule = new MultiLearnRule();  // Not sure about this at all! Memory leak? Crashes?
                       (yylhs.value.ifElseStatementVal) = new IfElseStatement(*(yystack_[6].value.opWithSeqVal), *(yystack_[2].value.multiLearnRuleVal), *empty_rule);
                   }
#line 740 "Parser.tab.cpp"
    break;

  case 21: // if_else_statement: "open if statement" operator_or_general_sequence "right parenthesis" "colon symbol" "end of line followed by indent" multi_learn_rule "end of line followed by undent" "open else statement" "end of line followed by indent" multi_learn_rule "end of line followed by undent" "close statement"
#line 255 "Parser.y"
                                                                                                                                                                     {
                       (yylhs.value.ifElseStatementVal) = new IfElseStatement(*(yystack_[10].value.opWithSeqVal), *(yystack_[6].value.multiLearnRuleVal), *(yystack_[2].value.multiLearnRuleVal));
                   }
#line 748 "Parser.tab.cpp"
    break;

  case 22: // for_statement: "open for statement" "operator label idx" "ket label idx" "infix in" operator_or_general_sequence "right parenthesis" "colon symbol" "end of line followed by indent" multi_learn_rule "end of line followed by undent" "close statement"
#line 260 "Parser.y"
                                                                                                                                            {
                  (yylhs.value.forStatementVal) = new ForStatement((yystack_[10].value.integerVal), (yystack_[9].value.ulongVal), (yystack_[8].value.ulongVal), *(yystack_[6].value.opWithSeqVal), *(yystack_[2].value.multiLearnRuleVal));
              }
#line 756 "Parser.tab.cpp"
    break;

  case 23: // while_statement: "open while statement" operator_or_general_sequence "right parenthesis" "colon symbol" "end of line followed by indent" multi_learn_rule "end of line followed by undent" "close statement"
#line 265 "Parser.y"
                                                                                                                    {
                    (yylhs.value.whileStatementVal) = new WhileStatement(*(yystack_[6].value.opWithSeqVal), *(yystack_[2].value.multiLearnRuleVal));
                }
#line 764 "Parser.tab.cpp"
    break;

  case 24: // multi_learn_rule: learn_rule
#line 270 "Parser.y"
                              { (yylhs.value.multiLearnRuleVal) = new MultiLearnRule(*(yystack_[0].value.learnRuleVal));  /* std::cout << "indent: " << $1 << "\n"; */ }
#line 770 "Parser.tab.cpp"
    break;

  case 25: // multi_learn_rule: operator_or_general_sequence
#line 271 "Parser.y"
                                                { (yylhs.value.multiLearnRuleVal) = new MultiLearnRule(*(yystack_[0].value.opWithSeqVal)); }
#line 776 "Parser.tab.cpp"
    break;

  case 26: // multi_learn_rule: if_else_statement
#line 272 "Parser.y"
                                     { (yylhs.value.multiLearnRuleVal) = new MultiLearnRule(*(yystack_[0].value.ifElseStatementVal)); }
#line 782 "Parser.tab.cpp"
    break;

  case 27: // multi_learn_rule: for_statement
#line 273 "Parser.y"
                                 { (yylhs.value.multiLearnRuleVal) = new MultiLearnRule(*(yystack_[0].value.forStatementVal)); }
#line 788 "Parser.tab.cpp"
    break;

  case 28: // multi_learn_rule: while_statement
#line 274 "Parser.y"
                                   { (yylhs.value.multiLearnRuleVal) = new MultiLearnRule(*(yystack_[0].value.whileStatementVal)); }
#line 794 "Parser.tab.cpp"
    break;

  case 29: // multi_learn_rule: multi_learn_rule "end of line followed by same depth" learn_rule
#line 275 "Parser.y"
                                                        { (yylhs.value.multiLearnRuleVal)->append(*(yystack_[0].value.learnRuleVal)); }
#line 800 "Parser.tab.cpp"
    break;

  case 30: // multi_learn_rule: multi_learn_rule "end of line followed by same depth" operator_or_general_sequence
#line 276 "Parser.y"
                                                                          { (yylhs.value.multiLearnRuleVal)->append(*(yystack_[0].value.opWithSeqVal)); }
#line 806 "Parser.tab.cpp"
    break;

  case 31: // multi_learn_rule: multi_learn_rule "end of line followed by same depth" "comment string"
#line 277 "Parser.y"
                                                     { }
#line 812 "Parser.tab.cpp"
    break;

  case 32: // multi_learn_rule: multi_learn_rule "end of line followed by same depth" if_else_statement
#line 278 "Parser.y"
                                                               { (yylhs.value.multiLearnRuleVal)->append(*(yystack_[0].value.ifElseStatementVal)); }
#line 818 "Parser.tab.cpp"
    break;

  case 33: // multi_learn_rule: multi_learn_rule "end of line followed by same depth" for_statement
#line 279 "Parser.y"
                                                           { (yylhs.value.multiLearnRuleVal)->append(*(yystack_[0].value.forStatementVal)); }
#line 824 "Parser.tab.cpp"
    break;

  case 34: // multi_learn_rule: multi_learn_rule "end of line followed by same depth" while_statement
#line 280 "Parser.y"
                                                             { (yylhs.value.multiLearnRuleVal)->append(*(yystack_[0].value.whileStatementVal)); }
#line 830 "Parser.tab.cpp"
    break;

  case 35: // function_learn_rule: "operator label idx" "function rule symbol" "learn symbol" operator_or_general_sequence
#line 283 "Parser.y"
                                                                             { std::shared_ptr<BaseSequence> tmp_ptr((yystack_[0].value.opWithSeqVal)); driver.context.fn_learn((yystack_[3].value.ulongVal), (yystack_[2].value.integerVal), tmp_ptr); }
#line 836 "Parser.tab.cpp"
    break;

  case 36: // function_learn_rule: "operator label idx" "function rule symbol" "learn symbol" "end of line followed by indent" multi_learn_rule
#line 284 "Parser.y"
                                                                            { std::shared_ptr<BaseSequence> tmp_ptr((yystack_[0].value.multiLearnRuleVal)); driver.context.fn_learn((yystack_[4].value.ulongVal), (yystack_[3].value.integerVal), tmp_ptr); }
#line 842 "Parser.tab.cpp"
    break;

  case 37: // function_learn_rule: "operator label idx" "left curley parenthesis" bound_function_parameters "right curley parenthesis" "learn symbol" operator_or_general_sequence
#line 285 "Parser.y"
                                                                                                                {
                        std::shared_ptr<BaseSequence> tmp_ptr((yystack_[0].value.opWithSeqVal)); driver.context.bound_fn_learn((yystack_[5].value.ulongVal), *(yystack_[3].value.paramVec), tmp_ptr);
                    }
#line 850 "Parser.tab.cpp"
    break;

  case 38: // function_learn_rule: "operator label idx" "left curley parenthesis" bound_function_parameters "right curley parenthesis" "learn symbol" "end of line followed by indent" multi_learn_rule
#line 288 "Parser.y"
                                                                                                               {
                        std::shared_ptr<BaseSequence> tmp_ptr((yystack_[0].value.multiLearnRuleVal)); driver.context.bound_fn_learn((yystack_[6].value.ulongVal), *(yystack_[4].value.paramVec), tmp_ptr);
                    }
#line 858 "Parser.tab.cpp"
    break;

  case 39: // bound_function_parameters: "operator label idx" "ket label idx"
#line 293 "Parser.y"
                                               { (yylhs.value.paramVec) = new std::vector<ulong>; (yylhs.value.paramVec)->push_back((yystack_[1].value.ulongVal)); (yylhs.value.paramVec)->push_back((yystack_[0].value.ulongVal)); }
#line 864 "Parser.tab.cpp"
    break;

  case 40: // bound_function_parameters: bound_function_parameters "comma" "operator label idx" "ket label idx"
#line 294 "Parser.y"
                                                                               { (yylhs.value.paramVec) = (yystack_[3].value.paramVec); (yylhs.value.paramVec)->push_back((yystack_[1].value.ulongVal)); (yylhs.value.paramVec)->push_back((yystack_[0].value.ulongVal)); }
#line 870 "Parser.tab.cpp"
    break;

  case 41: // operator_with_sequence: ket
#line 298 "Parser.y"
                             {
                            // std::cout << "naked ket: " << $1->to_string() << std::endl;
                            std::shared_ptr<BaseOperator> tmp_op_ptr = std::make_shared<SimpleOperator>("");
                            std::shared_ptr<BaseSequence> tmp_seq_ptr((yystack_[0].value.bSeq));
                            (yylhs.value.opWithSeqVal) = new OperatorWithSequence(tmp_op_ptr, tmp_seq_ptr);
                       }
#line 881 "Parser.tab.cpp"
    break;

  case 42: // operator_with_sequence: operator_sequence ket
#line 304 "Parser.y"
                                               {
                            // std::cout << $1->to_string() << $2->to_string() << std::endl;
                            std::shared_ptr<BaseOperator> tmp_op_ptr((yystack_[1].value.opSeqVal));
                            std::shared_ptr<BaseSequence> tmp_seq_ptr((yystack_[0].value.bSeq));
                            (yylhs.value.opWithSeqVal) = new OperatorWithSequence(tmp_op_ptr, tmp_seq_ptr);
                       }
#line 892 "Parser.tab.cpp"
    break;

  case 43: // operator_with_sequence: operator_sequence "left parenthesis" general_sequence "right parenthesis"
#line 310 "Parser.y"
                                                                          {
                            std::shared_ptr<BaseOperator> tmp_op_ptr((yystack_[3].value.opSeqVal));
                            std::shared_ptr<BaseSequence> tmp_seq_ptr((yystack_[1].value.opWithSeqVal));
                            (yylhs.value.opWithSeqVal) = new OperatorWithSequence(tmp_op_ptr, tmp_seq_ptr);
                       }
#line 902 "Parser.tab.cpp"
    break;

  case 44: // operator_sequence: general_operator
#line 317 "Parser.y"
                                     { std::shared_ptr<BaseOperator> tmp_ptr((yystack_[0].value.baseOpVal)); (yylhs.value.opSeqVal) = new OperatorSequence(tmp_ptr); }
#line 908 "Parser.tab.cpp"
    break;

  case 45: // operator_sequence: operator_sequence general_operator
#line 318 "Parser.y"
                                                       { (yylhs.value.opSeqVal) = (yystack_[1].value.opSeqVal); std::shared_ptr<BaseOperator> tmp_ptr((yystack_[0].value.baseOpVal)); (yylhs.value.opSeqVal)->append(tmp_ptr); }
#line 914 "Parser.tab.cpp"
    break;

  case 46: // compound_operator: "operator label idx" "left square parenthesis" parameters "right square parenthesis"
#line 338 "Parser.y"
                                                        { (yylhs.value.baseOpVal) = new CompoundOperator((yystack_[3].value.ulongVal), *(yystack_[1].value.constVec)); }
#line 920 "Parser.tab.cpp"
    break;

  case 47: // function_operator: "function label with left parenthesis" operator_or_general_sequence "right parenthesis"
#line 349 "Parser.y"
                                                                  { (yylhs.value.baseOpVal) = new FunctionOperator((yystack_[2].value.ulongVal), *(yystack_[1].value.opWithSeqVal)); }
#line 926 "Parser.tab.cpp"
    break;

  case 48: // function_operator: "function label with left parenthesis" operator_or_general_sequence "comma" operator_or_general_sequence "right parenthesis"
#line 350 "Parser.y"
                                                                                                     { (yylhs.value.baseOpVal) = new FunctionOperator((yystack_[4].value.ulongVal), *(yystack_[3].value.opWithSeqVal), *(yystack_[1].value.opWithSeqVal)); }
#line 932 "Parser.tab.cpp"
    break;

  case 49: // function_operator: "function label with left parenthesis" operator_or_general_sequence "comma" operator_or_general_sequence "comma" operator_or_general_sequence "right parenthesis"
#line 351 "Parser.y"
                                                                                                                                        { (yylhs.value.baseOpVal) = new FunctionOperator((yystack_[6].value.ulongVal), *(yystack_[5].value.opWithSeqVal), *(yystack_[3].value.opWithSeqVal), *(yystack_[1].value.opWithSeqVal)); }
#line 938 "Parser.tab.cpp"
    break;

  case 50: // function_operator: "function label with left parenthesis" operator_or_general_sequence "comma" operator_or_general_sequence "comma" operator_or_general_sequence "comma" operator_or_general_sequence "right parenthesis"
#line 352 "Parser.y"
                                                                                                                                                                           { (yylhs.value.baseOpVal) = new FunctionOperator((yystack_[8].value.ulongVal), *(yystack_[7].value.opWithSeqVal), *(yystack_[5].value.opWithSeqVal), *(yystack_[3].value.opWithSeqVal), *(yystack_[1].value.opWithSeqVal)); }
#line 944 "Parser.tab.cpp"
    break;

  case 51: // operator: function_operator
#line 359 "Parser.y"
                             { (yylhs.value.baseOpVal) = (yystack_[0].value.baseOpVal); }
#line 950 "Parser.tab.cpp"
    break;

  case 52: // operator: compound_operator
#line 360 "Parser.y"
                             { (yylhs.value.baseOpVal) = (yystack_[0].value.baseOpVal); }
#line 956 "Parser.tab.cpp"
    break;

  case 53: // operator: bracket_operator
#line 361 "Parser.y"
                            { (yylhs.value.baseOpVal) = (yystack_[0].value.bracketOpVal); }
#line 962 "Parser.tab.cpp"
    break;

  case 54: // operator: constant
#line 363 "Parser.y"
                    {
                switch ((yystack_[0].value.constVal)->type()) {
                    case COPERATOR : { (yylhs.value.baseOpVal) = new SimpleOperator((yystack_[0].value.constVal)->get_operator()); break; }
                    case CINT : { (yylhs.value.baseOpVal) = new NumericOperator((yystack_[0].value.constVal)->get_int()); break; }
                    case CFLOAT : { (yylhs.value.baseOpVal) = new NumericOperator((yystack_[0].value.constVal)->get_float()); break; }
                    default : { (yylhs.value.baseOpVal) = new EmptyOperator(); }
                }
         }
#line 975 "Parser.tab.cpp"
    break;

  case 55: // general_operator: operator
#line 373 "Parser.y"
                            { (yylhs.value.baseOpVal) = (yystack_[0].value.baseOpVal); }
#line 981 "Parser.tab.cpp"
    break;

  case 56: // general_operator: operator "power" "integer"
#line 374 "Parser.y"
                                          { std::shared_ptr<BaseOperator> tmp_ptr((yystack_[2].value.baseOpVal)); (yylhs.value.baseOpVal) = new PoweredOperator(tmp_ptr, (yystack_[0].value.integerVal)); }
#line 987 "Parser.tab.cpp"
    break;

  case 57: // general_sequence: operator_with_sequence
#line 377 "Parser.y"
                                          { (yylhs.value.opWithSeqVal) = (yystack_[0].value.opWithSeqVal); }
#line 993 "Parser.tab.cpp"
    break;

  case 58: // general_sequence: general_sequence "infix operator" operator_with_sequence
#line 378 "Parser.y"
                                                                    { (yylhs.value.opWithSeqVal) = (yystack_[2].value.opWithSeqVal); (yylhs.value.opWithSeqVal)->append((yystack_[1].value.integerVal), *(yystack_[0].value.opWithSeqVal)); }
#line 999 "Parser.tab.cpp"
    break;

  case 59: // general_sequence: general_sequence operator_with_sequence
#line 379 "Parser.y"
                                                           { (yylhs.value.opWithSeqVal) = (yystack_[1].value.opWithSeqVal); (yylhs.value.opWithSeqVal)->append(SPLUS, *(yystack_[0].value.opWithSeqVal)); }
#line 1005 "Parser.tab.cpp"
    break;

  case 60: // general_sequence: "left parenthesis" general_sequence "right parenthesis"
#line 380 "Parser.y"
                                                  {
                     // $$ = $2; $$->has_bracket(true);
                     // $2->has_bracket(true);
                     std::shared_ptr<BaseOperator> tmp_op_ptr = std::make_shared<SimpleOperator>("");
                     std::shared_ptr<BaseSequence> tmp_seq_ptr((yystack_[1].value.opWithSeqVal));
                     (yylhs.value.opWithSeqVal) = new OperatorWithSequence(tmp_op_ptr, tmp_seq_ptr);
                 }
#line 1017 "Parser.tab.cpp"
    break;

  case 61: // general_sequence: general_sequence "infix operator" "left parenthesis" general_sequence "right parenthesis"
#line 387 "Parser.y"
                                                                            {
                     (yylhs.value.opWithSeqVal) = (yystack_[4].value.opWithSeqVal);
                     std::shared_ptr<BaseOperator> tmp_op_ptr = std::make_shared<SimpleOperator>("");
                     std::shared_ptr<BaseSequence> tmp_seq_ptr((yystack_[1].value.opWithSeqVal));
                     OperatorWithSequence OpWithSeq = OperatorWithSequence(tmp_op_ptr, tmp_seq_ptr);
                     (yylhs.value.opWithSeqVal)->append((yystack_[3].value.integerVal), OpWithSeq);
                 }
#line 1029 "Parser.tab.cpp"
    break;

  case 62: // operator_or_general_sequence: general_sequence
#line 408 "Parser.y"
                                                { (yylhs.value.opWithSeqVal) = (yystack_[0].value.opWithSeqVal); }
#line 1035 "Parser.tab.cpp"
    break;

  case 63: // operator_or_general_sequence: operator_sequence
#line 409 "Parser.y"
                                                 {
                                 std::shared_ptr<BaseOperator> tmp_op_ptr((yystack_[0].value.opSeqVal));
                                 std::shared_ptr<BaseSequence> tmp_seq_ptr = std::make_shared<Ket>();
                                 (yylhs.value.opWithSeqVal) = new OperatorWithSequence(tmp_op_ptr, tmp_seq_ptr);
                             }
#line 1045 "Parser.tab.cpp"
    break;

  case 64: // constant: "string"
#line 416 "Parser.y"
                  { (yylhs.value.constVal) = new ConstantString(*(yystack_[0].value.stringVal)); }
#line 1051 "Parser.tab.cpp"
    break;

  case 65: // constant: "*"
#line 417 "Parser.y"
                { (yylhs.value.constVal) = new ConstantOperator("*"); }
#line 1057 "Parser.tab.cpp"
    break;

  case 66: // constant: "operator label idx"
#line 418 "Parser.y"
                    { (yylhs.value.constVal) = new ConstantOperator((yystack_[0].value.ulongVal)); }
#line 1063 "Parser.tab.cpp"
    break;

  case 67: // constant: "integer"
#line 419 "Parser.y"
                   { (yylhs.value.constVal) = new ConstantInteger((yystack_[0].value.integerVal)); }
#line 1069 "Parser.tab.cpp"
    break;

  case 68: // constant: "double"
#line 420 "Parser.y"
                  { (yylhs.value.constVal) = new ConstantFloat((yystack_[0].value.doubleVal)); }
#line 1075 "Parser.tab.cpp"
    break;

  case 69: // constant: "integer" "divide symbol" "integer"
#line 421 "Parser.y"
                                  { (yylhs.value.constVal) = new ConstantFloat((double)(yystack_[2].value.integerVal) / (double)(yystack_[0].value.integerVal)); }
#line 1081 "Parser.tab.cpp"
    break;

  case 70: // constant: "integer" "divide symbol" "double"
#line 422 "Parser.y"
                                 { (yylhs.value.constVal) = new ConstantFloat((double)(yystack_[2].value.integerVal) / (yystack_[0].value.doubleVal)); }
#line 1087 "Parser.tab.cpp"
    break;

  case 71: // constant: "double" "divide symbol" "integer"
#line 423 "Parser.y"
                                 { (yylhs.value.constVal) = new ConstantFloat((yystack_[2].value.doubleVal) / (double)(yystack_[0].value.integerVal)); }
#line 1093 "Parser.tab.cpp"
    break;

  case 72: // constant: "minus operator"
#line 424 "Parser.y"
                    { (yylhs.value.constVal) = new ConstantFloat(-1); }
#line 1099 "Parser.tab.cpp"
    break;

  case 73: // parameters: constant
#line 427 "Parser.y"
                      { (yylhs.value.constVec) = new std::vector<std::shared_ptr<CompoundConstant>>;
                        std::shared_ptr<CompoundConstant> tmp_ptr((yystack_[0].value.constVal));
                        (yylhs.value.constVec)->push_back(tmp_ptr);
                        }
#line 1108 "Parser.tab.cpp"
    break;

  case 74: // parameters: parameters constant
#line 431 "Parser.y"
                                 { (yylhs.value.constVec) = (yystack_[1].value.constVec);
                                   std::shared_ptr<CompoundConstant> tmp_ptr((yystack_[0].value.constVal));
                                   (yylhs.value.constVec)->back()->append(tmp_ptr);
           }
#line 1117 "Parser.tab.cpp"
    break;

  case 75: // parameters: parameters "comma" constant
#line 435 "Parser.y"
                                       { (yylhs.value.constVec) = (yystack_[2].value.constVec); std::shared_ptr<CompoundConstant> tmp_ptr((yystack_[0].value.constVal)); (yylhs.value.constVec)->push_back(tmp_ptr); }
#line 1123 "Parser.tab.cpp"
    break;

  case 76: // bracket_parameters: operator_sequence
#line 438 "Parser.y"
                                       { (yylhs.value.bracketOpVal) = new BracketOperator(*(yystack_[0].value.opSeqVal)); }
#line 1129 "Parser.tab.cpp"
    break;

  case 77: // bracket_parameters: "infix operator" operator_sequence
#line 439 "Parser.y"
                                                { (yylhs.value.bracketOpVal) = new BracketOperator((yystack_[1].value.integerVal), *(yystack_[0].value.opSeqVal)); }
#line 1135 "Parser.tab.cpp"
    break;

  case 78: // bracket_parameters: bracket_parameters "infix operator" operator_sequence
#line 440 "Parser.y"
                                                                   { (yylhs.value.bracketOpVal) = (yystack_[2].value.bracketOpVal); (yylhs.value.bracketOpVal)->append((yystack_[1].value.integerVal), *(yystack_[0].value.opSeqVal)); }
#line 1141 "Parser.tab.cpp"
    break;

  case 79: // bracket_operator: "left parenthesis" bracket_parameters "right parenthesis"
#line 443 "Parser.y"
                                                    { (yylhs.value.bracketOpVal) = (yystack_[1].value.bracketOpVal); }
#line 1147 "Parser.tab.cpp"
    break;


#line 1151 "Parser.tab.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -90;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     155,   -90,   -90,     8,    -1,   -90,   -90,   -90,   -15,    -8,
     -90,   -90,   -10,   451,   -90,   407,   -90,    17,    59,   190,
     -90,   -90,    85,    86,    88,    44,   473,   -90,   -90,    67,
     -90,   429,   103,   -90,   -90,   -90,   106,    15,    99,   100,
     266,   104,    96,   -90,    -5,    52,   473,   341,    19,   215,
     -90,   -90,   -90,   -90,   -90,   -90,   251,   407,   -90,   -90,
     112,   495,   116,   -90,   473,   -90,   -90,   -90,   -90,   -90,
     281,   -90,   -90,   507,   110,     5,   -90,   451,    52,   -90,
      52,   -90,   451,   115,   451,   -90,   -90,   -90,   -90,     4,
     121,   -90,   215,   -90,   363,   -90,   407,   -90,    52,   215,
     -90,   -90,   266,   -90,   -90,   122,   127,     6,    52,   120,
     134,   126,   -90,    90,   451,   111,   -90,   385,   111,   -90,
     311,   136,   -90,   451,   119,   113,   131,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   215,   -90,   -90,     7,   114,   451,
     132,   111,   -90,   451,   215,   150,   215,   151,    10,   142,
      35,   -90,     3,   139,   141,   143,   -90,   215,   -90,   215,
      37,    41,   145,   146,   -90,   -90
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     2,    13,     0,     0,    15,    16,    17,    67,    68,
      64,    14,    66,     0,    72,     0,    65,     0,     0,     0,
       4,    41,     0,     0,     0,    57,    63,    52,    51,    55,
      44,    62,     0,    54,    53,    10,     0,     0,     0,     0,
       0,     0,    66,    57,     0,     0,    76,     0,     0,     0,
       1,     3,     5,     7,     8,     9,     0,     0,    42,    45,
       0,     0,     0,    59,     0,     6,    11,    69,    70,    71,
       0,    66,    73,     0,     0,     0,    47,     0,    77,    60,
       0,    79,     0,     0,     0,    24,    26,    27,    28,     0,
      57,    25,     0,    18,     0,    56,     0,    58,    76,     0,
      35,    46,     0,    74,    39,     0,     0,     0,    78,     0,
       0,     0,    12,     0,     0,    19,    43,     0,    36,    75,
       0,     0,    48,     0,     0,     0,     0,    31,    29,    32,
      33,    34,    30,    61,     0,    37,    40,     0,     0,     0,
       0,    38,    49,     0,     0,     0,     0,     0,     0,     0,
       0,    50,     0,     0,     0,     0,    20,     0,    23,     0,
       0,     0,     0,     0,    22,    21
  };

  const short
  Parser::yypgoto_[] =
  {
     -90,   -90,   -90,   135,   -21,     1,   -90,    68,    72,    74,
     -89,   -90,   -90,     0,    -9,   -90,   -90,   -90,   -18,    -3,
       2,   -36,   -90,   -90,   -90
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,    18,    19,    20,    21,    85,    23,    86,    87,    88,
      89,    24,    75,    43,    26,    27,    28,    29,    30,    31,
      91,    33,    73,    48,    34
  };

  const unsigned char
  Parser::yytable_[] =
  {
      25,    22,    32,   115,    72,    58,    46,   112,    59,    39,
     118,    35,    47,    36,    40,    44,    41,    37,    76,    25,
      22,    32,    64,    77,    38,    58,    67,    68,    59,   122,
     142,    63,   105,   106,   123,   143,    78,   103,    64,    80,
     155,   156,    81,    58,   113,   141,    59,    63,    46,    90,
     113,   152,    64,    98,    94,   148,    49,   150,    93,    50,
      59,    97,    56,     8,     9,    10,   119,    42,   160,    13,
     161,   108,   100,    14,    62,   113,   154,   113,   162,   107,
      59,   113,   163,    16,   109,    64,   111,    46,    53,    54,
      59,    55,    90,   117,    63,   127,    60,     5,     6,    90,
       7,     8,     9,    10,    11,    42,    65,    13,    64,    66,
      69,    14,    15,    90,   128,   132,    93,    63,    70,    74,
      40,    16,   135,    95,   104,   137,    82,     8,     9,    10,
     110,    42,    83,    13,    90,    84,    45,    14,    62,   114,
     120,   145,   121,   124,    90,   147,    90,    16,   125,   126,
     136,   113,   138,   144,    52,     1,   139,    90,     2,    90,
       3,     4,     5,     6,   140,     7,     8,     9,    10,    11,
      12,   146,    13,   149,   151,   153,    14,    15,   157,   158,
       0,   129,   159,   164,   165,   130,    16,   131,     0,     0,
      51,     0,     0,     2,     0,     3,     4,     5,     6,    17,
       7,     8,     9,    10,    11,    12,     0,    13,     0,     0,
       0,    14,    15,     0,     0,     0,     0,     0,     0,     0,
       0,    16,     5,     6,     0,     7,     8,     9,    10,    11,
      42,     0,    13,     0,    17,     0,    14,    15,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,     0,     0,
       0,    82,     0,     0,     0,     0,     0,    83,     5,     6,
      84,     7,     8,     9,    10,    11,    42,     0,    13,     0,
       0,     0,    14,    15,     0,     0,     0,     8,     9,    10,
       0,    71,    16,     0,     0,     0,     0,    14,     5,     6,
      92,     7,     8,     9,    10,    11,    42,    16,    13,     0,
       0,     0,    14,    15,     0,     0,     0,     0,     0,     0,
       0,     0,    16,     0,     0,     0,     0,     0,     5,     6,
      99,     7,     8,     9,    10,    11,    42,     0,    13,     0,
       0,     0,    14,    15,     0,     0,     0,     0,     0,     0,
       0,     0,    16,     0,     0,     0,     0,     0,     5,     6,
     134,     7,     8,     9,    10,    11,    42,     0,    13,     0,
       0,    61,    14,    62,    79,     0,     0,     0,     0,     0,
       5,     6,    16,     7,     8,     9,    10,    11,    42,     0,
      13,     0,     0,    61,    14,    62,   116,     0,     0,     0,
       0,     0,     5,     6,    16,     7,     8,     9,    10,    11,
      42,     0,    13,     0,     0,    61,    14,    62,   133,     0,
       0,     0,     0,     0,     5,     6,    16,     7,     8,     9,
      10,    11,    42,     0,    13,     0,     0,    45,    14,    15,
       0,     0,     0,     0,     0,     0,     5,     6,    16,     7,
       8,     9,    10,    11,    42,     0,    13,     0,     0,    61,
      14,    62,     0,     0,     0,     0,     0,     0,     5,     6,
      16,     7,     8,     9,    10,    11,    42,     0,    13,     0,
       0,     0,    14,    15,     0,     0,     0,     0,     0,     0,
       5,     6,    16,     7,     8,     9,    10,    11,    42,     0,
      13,     0,     0,     0,    14,    57,     0,     0,     0,     0,
       0,     0,     5,     6,    16,     7,     8,     9,    10,    11,
      42,     0,    13,     0,     0,     0,    14,    96,     8,     9,
      10,     0,    71,     0,     0,     0,    16,     0,    14,     0,
       0,     0,   101,     0,     0,   102,     0,     0,    16
  };

  const short
  Parser::yycheck_[] =
  {
       0,     0,     0,    92,    40,    26,    15,     3,    26,    19,
      99,     3,    15,    14,    24,    13,    26,    32,    23,    19,
      19,    19,    31,    28,    32,    46,    11,    12,    46,    23,
      23,    31,    27,    28,    28,    28,    45,    73,    47,    20,
      37,    38,    23,    64,    40,   134,    64,    47,    57,    49,
      40,    41,    61,    62,    57,   144,    39,   146,    56,     0,
      78,    61,    18,    11,    12,    13,   102,    15,   157,    17,
     159,    80,    70,    21,    22,    40,    41,    40,    41,    77,
      98,    40,    41,    31,    82,    94,    84,    96,     3,     3,
     108,     3,    92,    96,    94,     5,    29,     7,     8,    99,
      10,    11,    12,    13,    14,    15,     3,    17,   117,     3,
      11,    21,    22,   113,   113,   113,   114,   117,    18,    15,
      24,    31,   120,    11,    14,   123,    36,    11,    12,    13,
      15,    15,    42,    17,   134,    45,    20,    21,    22,    18,
      18,   139,    15,    23,   144,   143,   146,    31,    14,    23,
      14,    40,    33,    39,    19,     0,    43,   157,     3,   159,
       5,     6,     7,     8,    33,    10,    11,    12,    13,    14,
      15,    39,    17,    23,    23,    33,    21,    22,    39,    38,
      -1,   113,    39,    38,    38,   113,    31,   113,    -1,    -1,
       0,    -1,    -1,     3,    -1,     5,     6,     7,     8,    44,
      10,    11,    12,    13,    14,    15,    -1,    17,    -1,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,     7,     8,    -1,    10,    11,    12,    13,    14,
      15,    -1,    17,    -1,    44,    -1,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    42,     7,     8,
      45,    10,    11,    12,    13,    14,    15,    -1,    17,    -1,
      -1,    -1,    21,    22,    -1,    -1,    -1,    11,    12,    13,
      -1,    15,    31,    -1,    -1,    -1,    -1,    21,     7,     8,
      39,    10,    11,    12,    13,    14,    15,    31,    17,    -1,
      -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,     7,     8,
      39,    10,    11,    12,    13,    14,    15,    -1,    17,    -1,
      -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,     7,     8,
      39,    10,    11,    12,    13,    14,    15,    -1,    17,    -1,
      -1,    20,    21,    22,    23,    -1,    -1,    -1,    -1,    -1,
       7,     8,    31,    10,    11,    12,    13,    14,    15,    -1,
      17,    -1,    -1,    20,    21,    22,    23,    -1,    -1,    -1,
      -1,    -1,     7,     8,    31,    10,    11,    12,    13,    14,
      15,    -1,    17,    -1,    -1,    20,    21,    22,    23,    -1,
      -1,    -1,    -1,    -1,     7,     8,    31,    10,    11,    12,
      13,    14,    15,    -1,    17,    -1,    -1,    20,    21,    22,
      -1,    -1,    -1,    -1,    -1,    -1,     7,     8,    31,    10,
      11,    12,    13,    14,    15,    -1,    17,    -1,    -1,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,     7,     8,
      31,    10,    11,    12,    13,    14,    15,    -1,    17,    -1,
      -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
       7,     8,    31,    10,    11,    12,    13,    14,    15,    -1,
      17,    -1,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,     7,     8,    31,    10,    11,    12,    13,    14,
      15,    -1,    17,    -1,    -1,    -1,    21,    22,    11,    12,
      13,    -1,    15,    -1,    -1,    -1,    31,    -1,    21,    -1,
      -1,    -1,    25,    -1,    -1,    28,    -1,    -1,    31
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     0,     3,     5,     6,     7,     8,    10,    11,    12,
      13,    14,    15,    17,    21,    22,    31,    44,    47,    48,
      49,    50,    51,    52,    57,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    70,     3,    14,    32,    32,    19,
      24,    26,    15,    59,    66,    20,    60,    65,    69,    39,
       0,     0,    49,     3,     3,     3,    18,    22,    50,    64,
      29,    20,    22,    59,    60,     3,     3,    11,    12,    11,
      18,    15,    67,    68,    15,    58,    23,    28,    60,    23,
      20,    23,    36,    42,    45,    51,    53,    54,    55,    56,
      59,    66,    39,    66,    65,    11,    22,    59,    60,    39,
      66,    25,    28,    67,    14,    27,    28,    66,    60,    66,
      15,    66,     3,    40,    18,    56,    23,    65,    56,    67,
      18,    15,    23,    28,    23,    14,    23,     5,    51,    53,
      54,    55,    66,    23,    39,    66,    14,    66,    33,    43,
      33,    56,    23,    28,    39,    66,    39,    66,    56,    23,
      56,    23,    41,    33,    41,    37,    38,    39,    38,    39,
      56,    56,    41,    41,    38,    38
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    46,    47,    47,    48,    48,    49,    49,    49,    49,
      49,    49,    49,    49,    50,    50,    50,    50,    51,    52,
      53,    53,    54,    55,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    57,    57,    57,    57,    58,
      58,    59,    59,    59,    60,    60,    61,    62,    62,    62,
      62,    63,    63,    63,    63,    64,    64,    65,    65,    65,
      65,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    68,    68,    68,    69,    69,    69,    70
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     2,     2,     2,     2,     2,
       2,     3,     4,     1,     1,     1,     1,     1,     3,     4,
       8,    12,    11,     8,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     4,     5,     6,     7,     2,
       4,     1,     2,     4,     1,     2,     4,     3,     5,     7,
       9,     1,     1,     1,     1,     1,     3,     1,     3,     2,
       3,     5,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     1,     1,     2,     3,     1,     2,     3,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"end of line\"",
  "\"white space char\"", "\"comment string\"", "\"context learn rule\"",
  "\"self ket\"", "\"multi self ket\"", "\"self ket k\"",
  "\"multi self ket k\"", "\"integer\"", "\"double\"", "\"string\"",
  "\"ket label idx\"", "\"operator label idx\"",
  "\"operator label idx with space\"",
  "\"function label with left parenthesis\"", "\"learn symbol\"",
  "\"function rule symbol\"", "\"infix operator\"", "\"minus operator\"",
  "\"left parenthesis\"", "\"right parenthesis\"",
  "\"left square parenthesis\"", "\"right square parenthesis\"",
  "\"left curley parenthesis\"", "\"right curley parenthesis\"",
  "\"comma\"", "\"power\"", "\"quotation symbol\"", "\"*\"",
  "\"divide symbol\"", "\"colon symbol\"", "\"end of line with space 4\"",
  "\"infix double operator\"", "\"open if statement\"",
  "\"open else statement\"", "\"close statement\"",
  "\"end of line followed by indent\"",
  "\"end of line followed by same depth\"",
  "\"end of line followed by undent\"", "\"open for statement\"",
  "\"infix in\"", "\"dollar symbol\"", "\"open while statement\"",
  "$accept", "start", "line", "item", "ket", "learn_rule",
  "general_learn_rule", "if_else_statement", "for_statement",
  "while_statement", "multi_learn_rule", "function_learn_rule",
  "bound_function_parameters", "operator_with_sequence",
  "operator_sequence", "compound_operator", "function_operator",
  "operator", "general_operator", "general_sequence",
  "operator_or_general_sequence", "constant", "parameters",
  "bracket_parameters", "bracket_operator", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   192,   192,   193,   195,   196,   203,   206,   207,   208,
     209,   210,   211,   212,   218,   219,   220,   221,   245,   248,
     251,   255,   260,   265,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   283,   284,   285,   288,   293,
     294,   298,   304,   310,   317,   318,   338,   349,   350,   351,
     352,   359,   360,   361,   363,   373,   374,   377,   378,   379,
     380,   387,   408,   409,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   427,   431,   435,   438,   439,   440,   443
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
    };
    // Last valid token kind.
    const int code_max = 300;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 34 "Parser.y"
} // SDB
#line 1863 "Parser.tab.cpp"

#line 446 "Parser.y"
 /*** Additional Code ***/

void SDB::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
