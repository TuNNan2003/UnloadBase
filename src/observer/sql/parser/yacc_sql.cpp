/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"
#include "function/function.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}


#line 116 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_CALC = 9,                       /* CALC  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_UPDATE = 16,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 20,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 21,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 22,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 23,                     /* INT_T  */
  YYSYMBOL_STRING_T = 24,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 25,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 26,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 27,                    /* TEXT_T  */
  YYSYMBOL_HELP = 28,                      /* HELP  */
  YYSYMBOL_EXIT = 29,                      /* EXIT  */
  YYSYMBOL_DOT = 30,                       /* DOT  */
  YYSYMBOL_INTO = 31,                      /* INTO  */
  YYSYMBOL_VALUES = 32,                    /* VALUES  */
  YYSYMBOL_FROM = 33,                      /* FROM  */
  YYSYMBOL_WHERE = 34,                     /* WHERE  */
  YYSYMBOL_AND = 35,                       /* AND  */
  YYSYMBOL_SET = 36,                       /* SET  */
  YYSYMBOL_ON = 37,                        /* ON  */
  YYSYMBOL_LOAD = 38,                      /* LOAD  */
  YYSYMBOL_DATA = 39,                      /* DATA  */
  YYSYMBOL_INFILE = 40,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 41,                   /* EXPLAIN  */
  YYSYMBOL_LENGTH_FUNC = 42,               /* LENGTH_FUNC  */
  YYSYMBOL_DATE_FORMAT_FUNC = 43,          /* DATE_FORMAT_FUNC  */
  YYSYMBOL_ROUND_FUNC = 44,                /* ROUND_FUNC  */
  YYSYMBOL_INNER = 45,                     /* INNER  */
  YYSYMBOL_JOIN = 46,                      /* JOIN  */
  YYSYMBOL_EQ = 47,                        /* EQ  */
  YYSYMBOL_LT = 48,                        /* LT  */
  YYSYMBOL_GT = 49,                        /* GT  */
  YYSYMBOL_LE = 50,                        /* LE  */
  YYSYMBOL_GE = 51,                        /* GE  */
  YYSYMBOL_NE = 52,                        /* NE  */
  YYSYMBOL_MAX = 53,                       /* MAX  */
  YYSYMBOL_MIN = 54,                       /* MIN  */
  YYSYMBOL_COUNT = 55,                     /* COUNT  */
  YYSYMBOL_AVG = 56,                       /* AVG  */
  YYSYMBOL_SUM = 57,                       /* SUM  */
  YYSYMBOL_LIKE = 58,                      /* LIKE  */
  YYSYMBOL_NOT = 59,                       /* NOT  */
  YYSYMBOL_AS = 60,                        /* AS  */
  YYSYMBOL_NULL_T = 61,                    /* NULL_T  */
  YYSYMBOL_NUMBER = 62,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 63,                     /* FLOAT  */
  YYSYMBOL_ID = 64,                        /* ID  */
  YYSYMBOL_DATE_STR = 65,                  /* DATE_STR  */
  YYSYMBOL_SSS = 66,                       /* SSS  */
  YYSYMBOL_67_ = 67,                       /* '+'  */
  YYSYMBOL_68_ = 68,                       /* '-'  */
  YYSYMBOL_69_ = 69,                       /* '*'  */
  YYSYMBOL_70_ = 70,                       /* '/'  */
  YYSYMBOL_UMINUS = 71,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_commands = 73,                  /* commands  */
  YYSYMBOL_command_wrapper = 74,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 75,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 76,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 77,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 78,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 79,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 80,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 81,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 82,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 83,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 84,         /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 85,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 86,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 87,             /* attr_def_list  */
  YYSYMBOL_attr_def = 88,                  /* attr_def  */
  YYSYMBOL_nullable = 89,                  /* nullable  */
  YYSYMBOL_number = 90,                    /* number  */
  YYSYMBOL_type = 91,                      /* type  */
  YYSYMBOL_insert_stmt = 92,               /* insert_stmt  */
  YYSYMBOL_tuple_list = 93,                /* tuple_list  */
  YYSYMBOL_value_list = 94,                /* value_list  */
  YYSYMBOL_value = 95,                     /* value  */
  YYSYMBOL_delete_stmt = 96,               /* delete_stmt  */
  YYSYMBOL_update_stmt = 97,               /* update_stmt  */
  YYSYMBOL_select_stmt = 98,               /* select_stmt  */
  YYSYMBOL_calc_stmt = 99,                 /* calc_stmt  */
  YYSYMBOL_expression_list = 100,          /* expression_list  */
  YYSYMBOL_expression = 101,               /* expression  */
  YYSYMBOL_select_attr = 102,              /* select_attr  */
  YYSYMBOL_alias = 103,                    /* alias  */
  YYSYMBOL_rel_attr = 104,                 /* rel_attr  */
  YYSYMBOL_complex_value = 105,            /* complex_value  */
  YYSYMBOL_attr_meta = 106,                /* attr_meta  */
  YYSYMBOL_id_meta = 107,                  /* id_meta  */
  YYSYMBOL_attr_list = 108,                /* attr_list  */
  YYSYMBOL_rel_list = 109,                 /* rel_list  */
  YYSYMBOL_where = 110,                    /* where  */
  YYSYMBOL_on = 111,                       /* on  */
  YYSYMBOL_condition_list = 112,           /* condition_list  */
  YYSYMBOL_condition = 113,                /* condition  */
  YYSYMBOL_join_tables = 114,              /* join_tables  */
  YYSYMBOL_comp_op = 115,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 116,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 117,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 118,        /* set_variable_stmt  */
  YYSYMBOL_set_list = 119,                 /* set_list  */
  YYSYMBOL_set_eq = 120,                   /* set_eq  */
  YYSYMBOL_opt_semicolon = 121             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   280

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  135
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  268

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   322


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    69,    67,     2,    68,     2,    70,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    71
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   209,   209,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   239,   245,   250,   256,   262,   268,   274,   281,
     287,   295,   309,   319,   338,   341,   354,   363,   371,   383,
     384,   385,   389,   392,   393,   394,   395,   398,   411,   417,
     426,   431,   438,   442,   446,   454,   459,   465,   477,   493,
     513,   527,   537,   547,   552,   563,   566,   569,   572,   575,
     579,   582,   590,   598,   611,   614,   620,   629,   638,   647,
     656,   662,   669,   676,   682,   692,   700,   711,   714,   721,
     729,   737,   745,   753,   761,   771,   783,   789,   795,   809,
     812,   821,   835,   838,   851,   854,   859,   862,   868,   871,
     876,   883,   895,   907,   919,   933,   942,   954,   961,   962,
     963,   964,   965,   966,   967,   968,   972,   985,   994,   997,
    1004,  1007,  1012,  1019,  1027,  1028
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "DESC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN",
  "LENGTH_FUNC", "DATE_FORMAT_FUNC", "ROUND_FUNC", "INNER", "JOIN", "EQ",
  "LT", "GT", "LE", "GE", "NE", "MAX", "MIN", "COUNT", "AVG", "SUM",
  "LIKE", "NOT", "AS", "NULL_T", "NUMBER", "FLOAT", "ID", "DATE_STR",
  "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "nullable", "number",
  "type", "insert_stmt", "tuple_list", "value_list", "value",
  "delete_stmt", "update_stmt", "select_stmt", "calc_stmt",
  "expression_list", "expression", "select_attr", "alias", "rel_attr",
  "complex_value", "attr_meta", "id_meta", "attr_list", "rel_list",
  "where", "on", "condition_list", "condition", "join_tables", "comp_op",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "set_list",
  "set_eq", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-212)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     149,    35,    47,    64,    52,   -46,    63,  -212,    40,    44,
      18,  -212,  -212,  -212,  -212,  -212,    54,   149,    83,    88,
    -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,    33,
      36,    48,    67,    64,  -212,  -212,  -212,  -212,  -212,    64,
    -212,  -212,    80,    52,   111,   118,   121,   127,   129,   134,
     135,   139,   125,  -212,  -212,   124,    73,  -212,  -212,  -212,
    -212,  -212,   102,   103,   132,   133,  -212,  -212,  -212,  -212,
     155,   137,  -212,   142,     6,  -212,    64,    64,    64,    64,
      64,    20,    70,   -42,   -12,   -42,   -42,   -42,   -42,   -42,
     119,    -1,    52,   122,  -212,    52,    52,    52,    52,   156,
    -212,   153,   154,   141,   154,   123,   159,   160,   161,  -212,
    -212,   -44,   -44,  -212,  -212,  -212,   178,   179,   187,   192,
     200,   207,   180,   209,   210,   211,   212,  -212,     0,     2,
     -11,    73,  -212,   -34,   -34,  -212,  -212,  -212,   214,   138,
    -212,   185,  -212,   215,  -212,   202,   191,   216,   219,  -212,
    -212,  -212,   171,   176,   177,   182,  -212,  -212,  -212,  -212,
    -212,   195,     1,   181,   201,   154,   203,  -212,   156,  -212,
     147,   222,   229,   231,   -19,   -19,  -212,   217,   147,   141,
     244,  -212,  -212,  -212,  -212,    -5,    61,   159,   233,   189,
     236,   238,   239,  -212,   240,  -212,   241,   197,  -212,   198,
    -212,    26,  -212,   242,   -42,   -42,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,   205,   138,   138,   138,  -212,  -212,   204,
     206,  -212,  -212,   182,  -212,   216,  -212,   246,  -212,  -212,
    -212,  -212,  -212,   228,   228,  -212,   147,   147,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,  -212,   248,  -212,  -212,   138,
    -212,  -212,  -212,    92,    -5,  -212,  -212,  -212
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,     0,     0,   134,
      21,    20,    14,    15,    16,    17,     9,    10,    11,    12,
      13,     8,     5,     7,     6,     4,     3,    18,    19,     0,
       0,     0,     0,     0,    56,    52,    53,    54,    55,     0,
      71,    62,    63,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    97,    96,    82,    61,    99,    83,    81,    87,
      30,    29,     0,     0,   128,     0,   127,     1,   135,     2,
       0,     0,    28,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    74,     0,     0,     0,     0,    99,
      72,     0,   104,   130,   104,     0,     0,     0,     0,    69,
      64,    65,    66,    67,    68,    80,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    98,     0,   102,
     104,    99,    75,    76,    77,    78,    79,    73,     0,   108,
      57,     0,   129,   131,    58,     0,     0,    34,     0,    32,
      84,    88,     0,     0,     0,     0,    89,    90,    91,    92,
      93,     0,     0,     0,     0,   104,     0,    60,    99,   100,
       0,    47,     0,     0,     0,     0,   105,   109,     0,   130,
       0,    43,    44,    45,    46,    39,    39,     0,     0,     0,
       0,     0,     0,    42,     0,   117,   102,     0,    59,     0,
     101,     0,    51,     0,     0,     0,   118,   119,   120,   121,
     122,   123,   124,     0,     0,     0,   108,   133,   132,     0,
       0,    40,    37,     0,    38,    34,    33,     0,    94,    86,
      85,    95,   103,   106,   106,    49,     0,     0,   125,   112,
     114,   111,   113,   110,   126,    41,     0,    35,    31,   108,
     116,   115,    50,     0,    39,   107,    48,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -212,  -212,   252,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,    37,    74,  -184,    41,  -212,
    -212,  -212,    23,    -4,  -212,  -212,  -212,  -212,   190,   -29,
    -212,   136,   -40,  -212,  -140,   -91,   -99,    69,  -103,    29,
    -211,  -212,   140,    94,  -212,  -212,  -212,    91,  -212,  -212
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,   198,   157,   232,   204,   196,
      32,   181,   211,    50,    33,    34,    35,    36,    51,    52,
      65,   109,    66,    67,    68,    69,   110,   175,   150,   260,
     186,   187,   140,   224,    37,    38,   114,   152,   153,    79
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,   127,   128,   131,   132,   133,   134,   135,   136,   185,
     147,   154,   234,    91,    84,   253,   138,   138,    70,   205,
      85,   173,    62,   149,   119,    89,    90,    63,   216,   217,
     218,   219,   220,   221,   176,   107,   108,   177,   125,   222,
     223,    39,   179,    40,   245,   246,   176,   174,   265,    64,
     129,   130,    62,    41,   230,    42,   231,    63,   121,   122,
     123,   124,   141,   139,   171,   143,   144,   145,   146,    53,
      71,    72,   208,    87,    88,    89,    90,    73,   233,   210,
     267,    43,    74,    77,   250,   252,   185,   105,   106,   107,
     108,    78,   102,    75,    54,    55,    56,    80,    64,    86,
      81,    64,    64,    64,    64,    57,    58,    59,    60,    61,
     266,   246,    82,    44,    45,    46,    62,    47,    48,   185,
     230,    63,   231,   127,   131,    44,    45,    46,    92,    47,
      48,    83,    49,   103,    62,    93,   126,   104,    94,    63,
     105,   106,   107,   108,    95,   184,    96,    87,    88,    89,
      90,    97,    98,     1,     2,   100,    99,   101,     3,     4,
       5,     6,     7,     8,     9,    10,   111,   112,   113,    11,
      12,    13,   116,   115,   117,   102,   212,    14,    15,   118,
     182,    55,   183,   137,   227,   148,   142,    16,   149,   155,
      17,    57,    58,    59,    60,    61,   160,   161,   166,    44,
      45,    46,    62,    47,    48,   151,   162,    63,    44,    45,
      46,   163,    47,    48,   191,   192,   193,   194,   195,   164,
     249,   251,   184,   156,   158,   159,   165,   167,   168,   169,
     170,   180,   188,   190,   189,   197,   199,   200,   201,   202,
     174,   213,   262,   212,   203,   206,   214,   207,   215,   209,
     229,   236,   226,   237,   238,   184,   239,   240,   241,   247,
     173,   243,   244,   248,   258,   259,   264,   255,   254,    76,
     263,   235,   257,   261,   256,   242,   120,   178,   172,   225,
     228
};

static const yytype_int16 yycheck[] =
{
       4,    92,    93,    94,    95,    96,    97,    98,    99,   149,
     109,   114,   196,    53,    43,   226,    17,    17,    64,    18,
      49,    19,    64,    34,    18,    69,    70,    69,    47,    48,
      49,    50,    51,    52,    45,    69,    70,   140,    18,    58,
      59,     6,   141,     8,    18,    19,    45,    45,   259,    53,
      62,    63,    64,     6,    59,     8,    61,    69,    87,    88,
      89,    90,   102,    64,    64,   105,   106,   107,   108,    17,
       7,    31,   175,    67,    68,    69,    70,    33,    17,   178,
     264,    17,    64,     0,   224,   225,   226,    67,    68,    69,
      70,     3,    19,    39,    42,    43,    44,    64,   102,    19,
      64,   105,   106,   107,   108,    53,    54,    55,    56,    57,
      18,    19,    64,    61,    62,    63,    64,    65,    66,   259,
      59,    69,    61,   214,   215,    61,    62,    63,    17,    65,
      66,    64,    68,    60,    64,    17,    66,    64,    17,    69,
      67,    68,    69,    70,    17,   149,    17,    67,    68,    69,
      70,    17,    17,     4,     5,    30,    17,    33,     9,    10,
      11,    12,    13,    14,    15,    16,    64,    64,    36,    20,
      21,    22,    17,    40,    37,    19,   180,    28,    29,    37,
      42,    43,    44,    64,   188,    32,    64,    38,    34,    66,
      41,    53,    54,    55,    56,    57,    18,    18,    18,    61,
      62,    63,    64,    65,    66,    64,    19,    69,    61,    62,
      63,    19,    65,    66,    23,    24,    25,    26,    27,    19,
     224,   225,   226,    64,    64,    64,    19,    18,    18,    18,
      18,    17,    47,    31,    19,    19,    17,    66,    62,    62,
      45,    19,   246,   247,    62,    64,    17,    46,    17,    46,
       6,    18,    35,    64,    18,   259,    18,    18,    18,    17,
      19,    64,    64,    58,    18,    37,    18,    61,    64,    17,
     247,   197,   235,   244,   233,   206,    86,   141,   138,   185,
     189
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    20,    21,    22,    28,    29,    38,    41,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    92,    96,    97,    98,    99,   116,   117,     6,
       8,     6,     8,    17,    61,    62,    63,    65,    66,    68,
      95,   100,   101,    17,    42,    43,    44,    53,    54,    55,
      56,    57,    64,    69,    95,   102,   104,   105,   106,   107,
      64,     7,    31,    33,    64,    39,    74,     0,     3,   121,
      64,    64,    64,    64,   101,   101,    19,    67,    68,    69,
      70,   104,    17,    17,    17,    17,    17,    17,    17,    17,
      30,    33,    19,    60,    64,    67,    68,    69,    70,   103,
     108,    64,    64,    36,   118,    40,    17,    37,    37,    18,
     100,   101,   101,   101,   101,    18,    66,   107,   107,    62,
      63,   107,   107,   107,   107,   107,   107,    64,    17,    64,
     114,   104,    64,   104,   104,   104,   104,   108,    32,    34,
     110,    64,   119,   120,   110,    66,    64,    88,    64,    64,
      18,    18,    19,    19,    19,    19,    18,    18,    18,    18,
      18,    64,   114,    19,    45,   109,    45,   110,   103,   108,
      17,    93,    42,    44,    95,   106,   112,   113,    47,    19,
      31,    23,    24,    25,    26,    27,    91,    19,    87,    17,
      66,    62,    62,    62,    90,    18,    64,    46,   110,    46,
     108,    94,    95,    19,    17,    17,    47,    48,    49,    50,
      51,    52,    58,    59,   115,   115,    35,    95,   119,     6,
      59,    61,    89,    17,    89,    88,    18,    64,    18,    18,
      18,    18,   109,    64,    64,    18,    19,    17,    58,    95,
     106,    95,   106,   112,    64,    61,    90,    87,    18,    37,
     111,   111,    95,    94,    18,   112,    18,    89
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    87,    88,    88,    88,    89,
      89,    89,    90,    91,    91,    91,    91,    92,    93,    93,
      94,    94,    95,    95,    95,    95,    95,    96,    97,    98,
      98,    98,    99,   100,   100,   101,   101,   101,   101,   101,
     101,   101,   102,   102,   103,   103,   104,   104,   104,   104,
     104,   104,   104,   104,   105,   105,   105,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   107,   107,   107,   108,
     108,   108,   109,   109,   110,   110,   111,   111,   112,   112,
     112,   113,   113,   113,   113,   114,   114,   114,   115,   115,
     115,   115,   115,   115,   115,   115,   116,   117,   118,   118,
     119,   119,   119,   120,   121,   121
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       2,     8,     5,     7,     0,     3,     6,     3,     3,     0,
       1,     2,     1,     1,     1,     1,     1,     5,     5,     3,
       3,     1,     1,     1,     1,     1,     1,     4,     4,     6,
       5,     2,     2,     1,     3,     3,     3,     3,     3,     3,
       2,     1,     2,     3,     1,     2,     3,     3,     3,     3,
       3,     1,     1,     1,     4,     6,     6,     1,     4,     4,
       4,     4,     4,     4,     6,     6,     1,     1,     3,     0,
       3,     4,     0,     3,     0,     2,     0,     2,     0,     1,
       3,     3,     3,     3,     3,     5,     5,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     7,     2,     0,     2,
       0,     1,     3,     3,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 210 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1821 "yacc_sql.cpp"
    break;

  case 22: /* exit_stmt: EXIT  */
#line 239 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1830 "yacc_sql.cpp"
    break;

  case 23: /* help_stmt: HELP  */
#line 245 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1838 "yacc_sql.cpp"
    break;

  case 24: /* sync_stmt: SYNC  */
#line 250 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1846 "yacc_sql.cpp"
    break;

  case 25: /* begin_stmt: TRX_BEGIN  */
#line 256 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1854 "yacc_sql.cpp"
    break;

  case 26: /* commit_stmt: TRX_COMMIT  */
#line 262 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1862 "yacc_sql.cpp"
    break;

  case 27: /* rollback_stmt: TRX_ROLLBACK  */
#line 268 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1870 "yacc_sql.cpp"
    break;

  case 28: /* drop_table_stmt: DROP TABLE ID  */
#line 274 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1880 "yacc_sql.cpp"
    break;

  case 29: /* show_tables_stmt: SHOW TABLES  */
#line 281 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1888 "yacc_sql.cpp"
    break;

  case 30: /* desc_table_stmt: DESC ID  */
#line 287 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1898 "yacc_sql.cpp"
    break;

  case 31: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID RBRACE  */
#line 296 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.attribute_name = (yyvsp[-1].string);
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 1913 "yacc_sql.cpp"
    break;

  case 32: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 310 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1925 "yacc_sql.cpp"
    break;

  case 33: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 320 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 1945 "yacc_sql.cpp"
    break;

  case 34: /* attr_def_list: %empty  */
#line 338 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1953 "yacc_sql.cpp"
    break;

  case 35: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 342 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1967 "yacc_sql.cpp"
    break;

  case 36: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 355 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable=(yyvsp[0].flag);
      free((yyvsp[-5].string));
    }
#line 1980 "yacc_sql.cpp"
    break;

  case 37: /* attr_def: ID TEXT_T nullable  */
#line 363 "yacc_sql.y"
                        {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)CHARS;
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = -1;
      (yyval.attr_info)->nullable=(yyvsp[0].flag);
      free((yyvsp[-2].string));
    }
#line 1993 "yacc_sql.cpp"
    break;

  case 38: /* attr_def: ID type nullable  */
#line 372 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable=(yyvsp[0].flag);
      free((yyvsp[-2].string));
    }
#line 2006 "yacc_sql.cpp"
    break;

  case 39: /* nullable: %empty  */
#line 383 "yacc_sql.y"
    { (yyval.flag)=true; }
#line 2012 "yacc_sql.cpp"
    break;

  case 40: /* nullable: NULL_T  */
#line 384 "yacc_sql.y"
            { (yyval.flag)=true; }
#line 2018 "yacc_sql.cpp"
    break;

  case 41: /* nullable: NOT NULL_T  */
#line 385 "yacc_sql.y"
                 { (yyval.flag)=false; }
#line 2024 "yacc_sql.cpp"
    break;

  case 42: /* number: NUMBER  */
#line 389 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2030 "yacc_sql.cpp"
    break;

  case 43: /* type: INT_T  */
#line 392 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2036 "yacc_sql.cpp"
    break;

  case 44: /* type: STRING_T  */
#line 393 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2042 "yacc_sql.cpp"
    break;

  case 45: /* type: FLOAT_T  */
#line 394 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2048 "yacc_sql.cpp"
    break;

  case 46: /* type: DATE_T  */
#line 395 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2054 "yacc_sql.cpp"
    break;

  case 47: /* insert_stmt: INSERT INTO ID VALUES tuple_list  */
#line 399 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      if ((yyvsp[0].tuple_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].tuple_list));
      }
      delete (yyvsp[0].tuple_list);
      free((yyvsp[-2].string));
    }
#line 2068 "yacc_sql.cpp"
    break;

  case 48: /* tuple_list: tuple_list COMMA LBRACE value_list RBRACE  */
#line 412 "yacc_sql.y"
    {
      (yyval.tuple_list) = (yyvsp[-4].tuple_list);
      (yyval.tuple_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2078 "yacc_sql.cpp"
    break;

  case 49: /* tuple_list: LBRACE value_list RBRACE  */
#line 418 "yacc_sql.y"
    {
      (yyval.tuple_list) = new std::vector<std::vector<Value>>();
      (yyval.tuple_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2088 "yacc_sql.cpp"
    break;

  case 50: /* value_list: value_list COMMA value  */
#line 426 "yacc_sql.y"
                           { 
      (yyval.value_list) = (yyvsp[-2].value_list);
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2098 "yacc_sql.cpp"
    break;

  case 51: /* value_list: value  */
#line 431 "yacc_sql.y"
           {
      (yyval.value_list) = new std::vector<Value>();
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2108 "yacc_sql.cpp"
    break;

  case 52: /* value: NUMBER  */
#line 438 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2117 "yacc_sql.cpp"
    break;

  case 53: /* value: FLOAT  */
#line 442 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2126 "yacc_sql.cpp"
    break;

  case 54: /* value: DATE_STR  */
#line 446 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp,true);
      free(tmp);
      if((yyval.value)->get_date()==nullptr||(yyval.value)->get_date()->isNull()){
        return ATTR_VAL_ERROR;
      }
    }
#line 2139 "yacc_sql.cpp"
    break;

  case 55: /* value: SSS  */
#line 454 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2149 "yacc_sql.cpp"
    break;

  case 56: /* value: NULL_T  */
#line 459 "yacc_sql.y"
            {
      (yyval.value) = new Value(AttrType::NULLTYPE);
    }
#line 2157 "yacc_sql.cpp"
    break;

  case 57: /* delete_stmt: DELETE FROM ID where  */
#line 466 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2171 "yacc_sql.cpp"
    break;

  case 58: /* update_stmt: UPDATE ID set_variable_stmt where  */
#line 478 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-2].string);
      if((yyvsp[-1].set_list) != nullptr){
        (yyval.sql_node)->update.setnode.swap(*(yyvsp[-1].set_list));
        delete (yyvsp[-1].set_list);
      }
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-2].string));
    }
#line 2189 "yacc_sql.cpp"
    break;

  case 59: /* select_stmt: SELECT select_attr FROM ID rel_list where  */
#line 494 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-4].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-4].rel_attr_list));
        delete (yyvsp[-4].rel_attr_list);
      }
      if ((yyvsp[-1].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-1].relation_list));
        delete (yyvsp[-1].relation_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-2].string));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-2].string));
    }
#line 2213 "yacc_sql.cpp"
    break;

  case 60: /* select_stmt: SELECT select_attr FROM join_tables where  */
#line 514 "yacc_sql.y"
    {
      /*递归解析JOIN语句*/
      (yyval.sql_node) = (yyvsp[-1].sql_node);
      if ((yyvsp[-3].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-3].rel_attr_list));
        delete (yyvsp[-3].rel_attr_list);
      }
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.insert((yyval.sql_node)->selection.conditions.begin(),(yyvsp[0].condition_list)->begin(),(yyvsp[0].condition_list)->end());
        delete (yyvsp[0].condition_list);
      }
      (yyval.sql_node)->selection.joinFlag=true;
    }
#line 2231 "yacc_sql.cpp"
    break;

  case 61: /* select_stmt: SELECT select_attr  */
#line 528 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[0].rel_attr_list));
        delete (yyvsp[0].rel_attr_list);
      }
    }
#line 2243 "yacc_sql.cpp"
    break;

  case 62: /* calc_stmt: CALC expression_list  */
#line 538 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2254 "yacc_sql.cpp"
    break;

  case 63: /* expression_list: expression  */
#line 548 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2263 "yacc_sql.cpp"
    break;

  case 64: /* expression_list: expression COMMA expression_list  */
#line 553 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2276 "yacc_sql.cpp"
    break;

  case 65: /* expression: expression '+' expression  */
#line 563 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2284 "yacc_sql.cpp"
    break;

  case 66: /* expression: expression '-' expression  */
#line 566 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2292 "yacc_sql.cpp"
    break;

  case 67: /* expression: expression '*' expression  */
#line 569 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2300 "yacc_sql.cpp"
    break;

  case 68: /* expression: expression '/' expression  */
#line 572 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2308 "yacc_sql.cpp"
    break;

  case 69: /* expression: LBRACE expression RBRACE  */
#line 575 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2317 "yacc_sql.cpp"
    break;

  case 70: /* expression: '-' expression  */
#line 579 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2325 "yacc_sql.cpp"
    break;

  case 71: /* expression: value  */
#line 582 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2335 "yacc_sql.cpp"
    break;

  case 72: /* select_attr: rel_attr attr_list  */
#line 590 "yacc_sql.y"
                       {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<ExpressionSqlNode*>;
      }
      (yyval.rel_attr_list)->emplace_back((yyvsp[-1].rel_attr));
    }
#line 2348 "yacc_sql.cpp"
    break;

  case 73: /* select_attr: rel_attr alias attr_list  */
#line 598 "yacc_sql.y"
                              {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<ExpressionSqlNode*>;
      }
      (yyvsp[-2].rel_attr)->name=(yyvsp[-1].string);
      (yyval.rel_attr_list)->emplace_back((yyvsp[-2].rel_attr));
      free((yyvsp[-1].string));
    }
#line 2363 "yacc_sql.cpp"
    break;

  case 74: /* alias: ID  */
#line 611 "yacc_sql.y"
      {
      (yyval.string)=(yyvsp[0].string);
    }
#line 2371 "yacc_sql.cpp"
    break;

  case 75: /* alias: AS ID  */
#line 614 "yacc_sql.y"
           {
      (yyval.string)=(yyvsp[0].string);
    }
#line 2379 "yacc_sql.cpp"
    break;

  case 76: /* rel_attr: rel_attr '+' rel_attr  */
#line 620 "yacc_sql.y"
                         {
      (yyval.rel_attr) = new ExpressionSqlNode;
      (yyval.rel_attr)->left=(yyvsp[-2].rel_attr);
      (yyval.rel_attr)->right=(yyvsp[0].rel_attr);
      (yyval.rel_attr)->calc=CalcOp::ADD;
      (yyval.rel_attr)->type=EXPRTYPE::EXPR;
      (yyval.rel_attr)->name=(yyvsp[-2].rel_attr)->name;
      (yyval.rel_attr)->name.append("+").append((yyvsp[0].rel_attr)->name);
    }
#line 2393 "yacc_sql.cpp"
    break;

  case 77: /* rel_attr: rel_attr '-' rel_attr  */
#line 629 "yacc_sql.y"
                           {
      (yyval.rel_attr) = new ExpressionSqlNode;
      (yyval.rel_attr)->left=(yyvsp[-2].rel_attr);
      (yyval.rel_attr)->right=(yyvsp[0].rel_attr);
      (yyval.rel_attr)->calc=CalcOp::SUB;
      (yyval.rel_attr)->type=EXPRTYPE::EXPR;
      (yyval.rel_attr)->name=(yyvsp[-2].rel_attr)->name;
      (yyval.rel_attr)->name.append("-").append((yyvsp[0].rel_attr)->name);
    }
#line 2407 "yacc_sql.cpp"
    break;

  case 78: /* rel_attr: rel_attr '*' rel_attr  */
#line 638 "yacc_sql.y"
                           {
      (yyval.rel_attr) = new ExpressionSqlNode;
      (yyval.rel_attr)->left=(yyvsp[-2].rel_attr);
      (yyval.rel_attr)->right=(yyvsp[0].rel_attr);
      (yyval.rel_attr)->calc=CalcOp::MUL;
      (yyval.rel_attr)->type=EXPRTYPE::EXPR;
      (yyval.rel_attr)->name=(yyvsp[-2].rel_attr)->name;
      (yyval.rel_attr)->name.append("*").append((yyvsp[0].rel_attr)->name);
    }
#line 2421 "yacc_sql.cpp"
    break;

  case 79: /* rel_attr: rel_attr '/' rel_attr  */
#line 647 "yacc_sql.y"
                           {
      (yyval.rel_attr) = new ExpressionSqlNode;
      (yyval.rel_attr)->left=(yyvsp[-2].rel_attr);
      (yyval.rel_attr)->right=(yyvsp[0].rel_attr);
      (yyval.rel_attr)->calc=CalcOp::DIV;
      (yyval.rel_attr)->type=EXPRTYPE::EXPR;
      (yyval.rel_attr)->name=(yyvsp[-2].rel_attr)->name;
      (yyval.rel_attr)->name.append("/").append((yyvsp[0].rel_attr)->name);
    }
#line 2435 "yacc_sql.cpp"
    break;

  case 80: /* rel_attr: LBRACE rel_attr RBRACE  */
#line 656 "yacc_sql.y"
                            {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      std::string str=(yyvsp[-1].rel_attr)->name;
      (yyval.rel_attr)->name="(";
      (yyval.rel_attr)->name.append(str).append(")");
    }
#line 2446 "yacc_sql.cpp"
    break;

  case 81: /* rel_attr: attr_meta  */
#line 662 "yacc_sql.y"
               {
      (yyval.rel_attr) = new ExpressionSqlNode;
      (yyval.rel_attr)->attr=*(yyvsp[0].attr_meta);
      (yyval.rel_attr)->type=EXPRTYPE::ATTR;
      (yyval.rel_attr)->name=(yyvsp[0].attr_meta)->name;
      free((yyvsp[0].attr_meta));
    }
#line 2458 "yacc_sql.cpp"
    break;

  case 82: /* rel_attr: value  */
#line 669 "yacc_sql.y"
           {
      (yyval.rel_attr) = new ExpressionSqlNode;
      (yyval.rel_attr)->value=*(yyvsp[0].value);
      (yyval.rel_attr)->type=EXPRTYPE::VAL;
      (yyval.rel_attr)->name=(yyvsp[0].value)->to_string();
      delete (yyvsp[0].value);
    }
#line 2470 "yacc_sql.cpp"
    break;

  case 83: /* rel_attr: complex_value  */
#line 676 "yacc_sql.y"
                   {
      (yyval.rel_attr) = (yyvsp[0].complex_value);
    }
#line 2478 "yacc_sql.cpp"
    break;

  case 84: /* complex_value: LENGTH_FUNC LBRACE SSS RBRACE  */
#line 682 "yacc_sql.y"
                                 {
      (yyval.complex_value) = new ExpressionSqlNode;
      std::string str=std::string((yyvsp[-1].string));
      (yyval.complex_value)->name = "length";
      (yyval.complex_value)->name.append("(").append(str).append(")"); 
      int len = SQLFunction::length((yyvsp[-1].string))-2;
      (yyval.complex_value)->value=Value(len);
      (yyval.complex_value)->type=EXPRTYPE::VAL;
      free((yyvsp[-1].string));
    }
#line 2493 "yacc_sql.cpp"
    break;

  case 85: /* complex_value: ROUND_FUNC LBRACE FLOAT COMMA NUMBER RBRACE  */
#line 692 "yacc_sql.y"
                                                 {
      (yyval.complex_value) = new ExpressionSqlNode;
      (yyval.complex_value)->name = "round";
      (yyval.complex_value)->name.append("(").append(std::to_string((yyvsp[-3].floats))).append(",").append(std::to_string((yyvsp[-1].number))).append(")");
      float num = SQLFunction::round((yyvsp[-3].floats),(yyvsp[-1].number));
      (yyval.complex_value)->value=Value(num);
      (yyval.complex_value)->type=EXPRTYPE::VAL;
    }
#line 2506 "yacc_sql.cpp"
    break;

  case 86: /* complex_value: ROUND_FUNC LBRACE NUMBER COMMA NUMBER RBRACE  */
#line 700 "yacc_sql.y"
                                                  {
      (yyval.complex_value) = new ExpressionSqlNode;
      (yyval.complex_value)->name = "round";
      (yyval.complex_value)->name.append("(").append(std::to_string((yyvsp[-3].number))).append(",").append(std::to_string((yyvsp[-1].number))).append(")"); 
      float num = SQLFunction::round((yyvsp[-3].number),(yyvsp[-1].number));
      (yyval.complex_value)->value=Value(num);
      (yyval.complex_value)->type=EXPRTYPE::VAL;
    }
#line 2519 "yacc_sql.cpp"
    break;

  case 87: /* attr_meta: id_meta  */
#line 711 "yacc_sql.y"
           {
      (yyval.attr_meta) = (yyvsp[0].id_meta);
    }
#line 2527 "yacc_sql.cpp"
    break;

  case 88: /* attr_meta: LENGTH_FUNC LBRACE id_meta RBRACE  */
#line 714 "yacc_sql.y"
                                       {
      (yyval.attr_meta) = (yyvsp[-1].id_meta);
      std::string str=(yyvsp[-1].id_meta)->name;
      (yyval.attr_meta)->function_name = FunctionName::LENGTH; 
      (yyval.attr_meta)->name="length";
      (yyval.attr_meta)->name.append("(").append(str).append(")"); 
    }
#line 2539 "yacc_sql.cpp"
    break;

  case 89: /* attr_meta: MAX LBRACE id_meta RBRACE  */
#line 721 "yacc_sql.y"
                               {
      (yyval.attr_meta) = (yyvsp[-1].id_meta);
      std::string str=(yyvsp[-1].id_meta)->name;
      (yyval.attr_meta)->function_name = FunctionName::AGGREGATE_MAX;
      (yyval.attr_meta)->sql_type =  SqlCalculateType::AGGREGATE;  
      (yyval.attr_meta)->name="max";
      (yyval.attr_meta)->name.append("(").append(str).append(")"); 
    }
#line 2552 "yacc_sql.cpp"
    break;

  case 90: /* attr_meta: MIN LBRACE id_meta RBRACE  */
#line 729 "yacc_sql.y"
                               {
      (yyval.attr_meta) = (yyvsp[-1].id_meta);
      std::string str=(yyvsp[-1].id_meta)->name;
      (yyval.attr_meta)->function_name = FunctionName::AGGREGATE_MIN;
      (yyval.attr_meta)->sql_type = SqlCalculateType::AGGREGATE;
      (yyval.attr_meta)->name="min";
      (yyval.attr_meta)->name.append("(").append(str).append(")"); 
    }
#line 2565 "yacc_sql.cpp"
    break;

  case 91: /* attr_meta: COUNT LBRACE id_meta RBRACE  */
#line 737 "yacc_sql.y"
                                 {
      (yyval.attr_meta) = (yyvsp[-1].id_meta);
      std::string str=(yyvsp[-1].id_meta)->name;
      (yyval.attr_meta)->function_name = FunctionName::AGGREGATE_COUNT;
      (yyval.attr_meta)->sql_type = SqlCalculateType::AGGREGATE;
      (yyval.attr_meta)->name="count";
      (yyval.attr_meta)->name.append("(").append(str).append(")"); 
    }
#line 2578 "yacc_sql.cpp"
    break;

  case 92: /* attr_meta: AVG LBRACE id_meta RBRACE  */
#line 745 "yacc_sql.y"
                               {
      (yyval.attr_meta) = (yyvsp[-1].id_meta);
      std::string str=(yyvsp[-1].id_meta)->name;
      (yyval.attr_meta)->function_name = FunctionName::AGGREGATE_AVG;
      (yyval.attr_meta)->sql_type = SqlCalculateType::AGGREGATE;
      (yyval.attr_meta)->name="avg";
      (yyval.attr_meta)->name.append("(").append(str).append(")"); 
    }
#line 2591 "yacc_sql.cpp"
    break;

  case 93: /* attr_meta: SUM LBRACE id_meta RBRACE  */
#line 753 "yacc_sql.y"
                               {
      (yyval.attr_meta) = (yyvsp[-1].id_meta);
      std::string str=(yyvsp[-1].id_meta)->name;
      (yyval.attr_meta)->function_name = FunctionName::AGGREGATE_SUM;
      (yyval.attr_meta)->sql_type = SqlCalculateType::AGGREGATE;
      (yyval.attr_meta)->name="sum";
      (yyval.attr_meta)->name.append("(").append(str).append(")"); 
    }
#line 2604 "yacc_sql.cpp"
    break;

  case 94: /* attr_meta: DATE_FORMAT_FUNC LBRACE id_meta COMMA SSS RBRACE  */
#line 761 "yacc_sql.y"
                                                      {
      (yyval.attr_meta) = (yyvsp[-3].id_meta);
      std::string str=(yyvsp[-3].id_meta)->name;
      (yyval.attr_meta)->param.str_info = (yyvsp[-1].string); 
      (yyval.attr_meta)->param.type=ParamType::STR_PARAM;
      (yyval.attr_meta)->function_name = FunctionName::DATE_FORMAT; 
      (yyval.attr_meta)->name="date_format";
      (yyval.attr_meta)->name.append("(").append(str).append(",").append((yyvsp[-1].string)).append(")"); 
      free((yyvsp[-1].string));
    }
#line 2619 "yacc_sql.cpp"
    break;

  case 95: /* attr_meta: ROUND_FUNC LBRACE id_meta COMMA number RBRACE  */
#line 771 "yacc_sql.y"
                                                   {
      (yyval.attr_meta) = (yyvsp[-3].id_meta);
      std::string str=(yyvsp[-3].id_meta)->name;
      (yyval.attr_meta)->param.num_info.int_value_ = (yyvsp[-1].number); 
      (yyval.attr_meta)->param.type=ParamType::INT_PARAM;
      (yyval.attr_meta)->function_name = FunctionName::ROUND;
      (yyval.attr_meta)->name="round";
      (yyval.attr_meta)->name.append("(").append(str).append(",").append(std::to_string((yyvsp[-1].number))).append(")"); 
    }
#line 2633 "yacc_sql.cpp"
    break;

  case 96: /* id_meta: '*'  */
#line 783 "yacc_sql.y"
       {
      (yyval.id_meta) = new RelAttrSqlNode;
      (yyval.id_meta)->relation_name  = "";
      (yyval.id_meta)->attribute_name = "*";
      (yyval.id_meta)->name=std::string("*");
    }
#line 2644 "yacc_sql.cpp"
    break;

  case 97: /* id_meta: ID  */
#line 789 "yacc_sql.y"
         {
      (yyval.id_meta) = new RelAttrSqlNode;
      (yyval.id_meta)->attribute_name = (yyvsp[0].string);
      (yyval.id_meta)->name = std::string((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2655 "yacc_sql.cpp"
    break;

  case 98: /* id_meta: ID DOT ID  */
#line 795 "yacc_sql.y"
                {
      (yyval.id_meta) = new RelAttrSqlNode;
      (yyval.id_meta)->relation_name  = (yyvsp[-2].string);
      (yyval.id_meta)->attribute_name = (yyvsp[0].string);
      (yyval.id_meta)->name=std::string((yyvsp[-2].string));
      (yyval.id_meta)->name.append(".");
      (yyval.id_meta)->name.append((yyvsp[0].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2670 "yacc_sql.cpp"
    break;

  case 99: /* attr_list: %empty  */
#line 809 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2678 "yacc_sql.cpp"
    break;

  case 100: /* attr_list: COMMA rel_attr attr_list  */
#line 812 "yacc_sql.y"
                               {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<ExpressionSqlNode *>;
      }

      (yyval.rel_attr_list)->emplace_back((yyvsp[-1].rel_attr));
    }
#line 2692 "yacc_sql.cpp"
    break;

  case 101: /* attr_list: COMMA rel_attr alias attr_list  */
#line 821 "yacc_sql.y"
                                    {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<ExpressionSqlNode*>;
      }
      (yyvsp[-2].rel_attr)->name=(yyvsp[-1].string);
      (yyval.rel_attr_list)->emplace_back((yyvsp[-2].rel_attr));
      free((yyvsp[-1].string));
    }
#line 2707 "yacc_sql.cpp"
    break;

  case 102: /* rel_list: %empty  */
#line 835 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2715 "yacc_sql.cpp"
    break;

  case 103: /* rel_list: COMMA ID rel_list  */
#line 838 "yacc_sql.y"
                        {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }

      (yyval.relation_list)->push_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2730 "yacc_sql.cpp"
    break;

  case 104: /* where: %empty  */
#line 851 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2738 "yacc_sql.cpp"
    break;

  case 105: /* where: WHERE condition_list  */
#line 854 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2746 "yacc_sql.cpp"
    break;

  case 106: /* on: %empty  */
#line 859 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2754 "yacc_sql.cpp"
    break;

  case 107: /* on: ON condition_list  */
#line 862 "yacc_sql.y"
                        {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2762 "yacc_sql.cpp"
    break;

  case 108: /* condition_list: %empty  */
#line 868 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2770 "yacc_sql.cpp"
    break;

  case 109: /* condition_list: condition  */
#line 871 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2780 "yacc_sql.cpp"
    break;

  case 110: /* condition_list: condition AND condition_list  */
#line 876 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2790 "yacc_sql.cpp"
    break;

  case 111: /* condition: attr_meta comp_op value  */
#line 884 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].attr_meta);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].attr_meta);
      delete (yyvsp[0].value);
    }
#line 2806 "yacc_sql.cpp"
    break;

  case 112: /* condition: value comp_op value  */
#line 896 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 2822 "yacc_sql.cpp"
    break;

  case 113: /* condition: attr_meta comp_op attr_meta  */
#line 908 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].attr_meta);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].attr_meta);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].attr_meta);
      delete (yyvsp[0].attr_meta);
    }
#line 2838 "yacc_sql.cpp"
    break;

  case 114: /* condition: value comp_op attr_meta  */
#line 920 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].attr_meta);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].attr_meta);
    }
#line 2854 "yacc_sql.cpp"
    break;

  case 115: /* join_tables: join_tables INNER JOIN ID on  */
#line 933 "yacc_sql.y"
                                {
      (yyval.sql_node) = (yyvsp[-4].sql_node);
      if((yyvsp[0].condition_list)!=nullptr){
        (yyval.sql_node)->selection.conditions.insert((yyval.sql_node)->selection.conditions.begin(),(yyvsp[0].condition_list)->begin(),(yyvsp[0].condition_list)->end());
        delete (yyvsp[0].condition_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2868 "yacc_sql.cpp"
    break;

  case 116: /* join_tables: ID INNER JOIN ID on  */
#line 943 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if((yyvsp[0].condition_list)!=nullptr){
        (yyval.sql_node)->selection.conditions.insert((yyval.sql_node)->selection.conditions.begin(),(yyvsp[0].condition_list)->begin(),(yyvsp[0].condition_list)->end());
        delete (yyvsp[0].condition_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-4].string));
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-1].string));
      free((yyvsp[-4].string));
      free((yyvsp[-1].string));
    }
#line 2884 "yacc_sql.cpp"
    break;

  case 117: /* join_tables: LBRACE join_tables RBRACE  */
#line 955 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[-1].sql_node);
    }
#line 2892 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: EQ  */
#line 961 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2898 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: LT  */
#line 962 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2904 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: GT  */
#line 963 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2910 "yacc_sql.cpp"
    break;

  case 121: /* comp_op: LE  */
#line 964 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2916 "yacc_sql.cpp"
    break;

  case 122: /* comp_op: GE  */
#line 965 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2922 "yacc_sql.cpp"
    break;

  case 123: /* comp_op: NE  */
#line 966 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2928 "yacc_sql.cpp"
    break;

  case 124: /* comp_op: LIKE  */
#line 967 "yacc_sql.y"
           { (yyval.comp) =  LIKE_OP; }
#line 2934 "yacc_sql.cpp"
    break;

  case 125: /* comp_op: NOT LIKE  */
#line 968 "yacc_sql.y"
                {(yyval.comp) = NOT_LIKE_OP;}
#line 2940 "yacc_sql.cpp"
    break;

  case 126: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 973 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 2954 "yacc_sql.cpp"
    break;

  case 127: /* explain_stmt: EXPLAIN command_wrapper  */
#line 986 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 2963 "yacc_sql.cpp"
    break;

  case 128: /* set_variable_stmt: %empty  */
#line 994 "yacc_sql.y"
    {
      (yyval.set_list) = nullptr;
    }
#line 2971 "yacc_sql.cpp"
    break;

  case 129: /* set_variable_stmt: SET set_list  */
#line 997 "yacc_sql.y"
                   {
      (yyval.set_list) = (yyvsp[0].set_list);
    }
#line 2979 "yacc_sql.cpp"
    break;

  case 130: /* set_list: %empty  */
#line 1004 "yacc_sql.y"
  {
    (yyval.set_list) = nullptr;
  }
#line 2987 "yacc_sql.cpp"
    break;

  case 131: /* set_list: set_eq  */
#line 1007 "yacc_sql.y"
           {
    (yyval.set_list) = new std::vector<SetVariableSqlNode>;
    (yyval.set_list)->emplace_back(*(yyvsp[0].set_eq));
    delete (yyvsp[0].set_eq);
  }
#line 2997 "yacc_sql.cpp"
    break;

  case 132: /* set_list: set_eq COMMA set_list  */
#line 1012 "yacc_sql.y"
                         {
    (yyval.set_list) = (yyvsp[0].set_list);
    (yyval.set_list)->emplace_back(*(yyvsp[-2].set_eq));
    delete (yyvsp[-2].set_eq); 
  }
#line 3007 "yacc_sql.cpp"
    break;

  case 133: /* set_eq: ID EQ value  */
#line 1019 "yacc_sql.y"
                {
      (yyval.set_eq) = new SetVariableSqlNode;
      (yyval.set_eq)->name  = (yyvsp[-2].string);
      (yyval.set_eq)->value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3019 "yacc_sql.cpp"
    break;


#line 3023 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1030 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
