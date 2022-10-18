#define BOOST_TEST_MODULE TestHyperRoute_GithubApi
#include <hyperoute/backend/boost.hpp>
#include <hyperoute/backend/hyperscan.hpp>
#include <hyperoute/backend/simple.hpp>
#include <hyperoute/builder.hpp>
#include <hyperoute/router.hpp>

#include <turtle/mock.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/included/unit_test.hpp>

struct Github_Fixture
{
    Github_Fixture() {}

    ~Github_Fixture() {}

    template<typename Backend>
    std::optional<hyperoute::router> create_router(Backend backend)
    {
        hyperoute::builder builder(backend);

        std::error_condition ec;

        // clang-format off

        // OAuth Authorizations
        builder.add_route("/authorizations"                                 , ec, ctx_1).methods({"GET"});
        builder.add_route("/authorizations/{id}"                            , ec, ctx_2).methods({"GET"});
        builder.add_route("/authorizations"                                 , ec, ctx_3).methods({"POST"});
        builder.add_route("/authorizations/clients/{client_id}"             , ec, ctx_4).methods({"PUT"});
        builder.add_route("/authorizations/{id}"                            , ec, ctx_5).methods({"PATCH"});
        builder.add_route("/authorizations/{id}"                            , ec, ctx_6).methods({"DELETE"});
        builder.add_route("/applications/{client_id}/tokens/{access_token}" , ec, ctx_7).methods({"GET"});
        builder.add_route("/applications/{client_id}/tokens"                , ec, ctx_8).methods({"DELETE"});
        builder.add_route("/applications/{client_id}/tokens/{access_token}" , ec, ctx_9).methods({"DELETE"});

        // Activity
        builder.add_route("/events"                                 , ec, ctx_10).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/events"            , ec, ctx_11).methods({"GET"});
        builder.add_route("/networks/{owner}/{repo}/events"         , ec, ctx_12).methods({"GET"});
        builder.add_route("/orgs/{org}/events"                      , ec, ctx_13).methods({"GET"});
        builder.add_route("/users/{user}/received_events"           , ec, ctx_14).methods({"GET"});
        builder.add_route("/users/{user}/received_events/public"    , ec, ctx_15).methods({"GET"});
        builder.add_route("/users/{user}/events"                    , ec, ctx_16).methods({"GET"});
        builder.add_route("/users/{user}/events/public"             , ec, ctx_17).methods({"GET"});
        builder.add_route("/users/{user}/events/orgs/{org}"         , ec, ctx_18).methods({"GET"});
        builder.add_route("/feeds"                                  , ec, ctx_19).methods({"GET"});
        builder.add_route("/notifications"                          , ec, ctx_20).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/notifications"     , ec, ctx_21).methods({"GET"});
        builder.add_route("/notifications"                          , ec, ctx_22).methods({"PUT"});
        builder.add_route("/repos/{owner}/{repo}/notifications"     , ec, ctx_23).methods({"PUT"});
        builder.add_route("/notifications/threads/{id}"             , ec, ctx_24).methods({"GET"});
        builder.add_route("/notifications/threads/{id}"             , ec, ctx_25).methods({"PATCH"});
        builder.add_route("/notifications/threads/{id}/subscription", ec, ctx_26).methods({"GET"});
        builder.add_route("/notifications/threads/{id}/subscription", ec, ctx_27).methods({"PUT"});
        builder.add_route("/notifications/threads/{id}/subscription", ec, ctx_28).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/stargazers"        , ec, ctx_29).methods({"GET"});
        builder.add_route("/users/{user}/starred"                   , ec, ctx_30).methods({"GET"});
        builder.add_route("/user/starred"                           , ec, ctx_31).methods({"GET"});
        builder.add_route("/user/starred/{owner}/{repo}"            , ec, ctx_32).methods({"GET"});
        builder.add_route("/user/starred/{owner}/{repo}"            , ec, ctx_33).methods({"PUT"});
        builder.add_route("/user/starred/{owner}/{repo}"            , ec, ctx_34).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/subscribers"       , ec, ctx_35).methods({"GET"});
        builder.add_route("/users/{user}/subscriptions"             , ec, ctx_36).methods({"GET"});
        builder.add_route("/user/subscriptions"                     , ec, ctx_37).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/subscription"      , ec, ctx_38).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/subscription"      , ec, ctx_39).methods({"PUT"});
        builder.add_route("/repos/{owner}/{repo}/subscription"      , ec, ctx_40).methods({"DELETE"});
        builder.add_route("/user/subscriptions/{owner}/{repo}"      , ec, ctx_41).methods({"GET"});
        builder.add_route("/user/subscriptions/{owner}/{repo}"      , ec, ctx_42).methods({"PUT"});
        builder.add_route("/user/subscriptions/{owner}/{repo}"      , ec, ctx_43).methods({"DELETE"});

        // Gists
        builder.add_route("/users/{user}/gists"     , ec, ctx_44).methods({"GET"});
        builder.add_route("/gists"                  , ec, ctx_45).methods({"GET"});
        builder.add_route("/gists/public"           , ec, ctx_46).methods({"GET"});
        builder.add_route("/gists/starred"          , ec, ctx_47).methods({"GET"});
        builder.add_route("/gists/{id}"             , ec, ctx_48).methods({"GET"});
        builder.add_route("/gists"                  , ec, ctx_49).methods({"POST"});
        builder.add_route("/gists/{id}"             , ec, ctx_50).methods({"PATCH"});
        builder.add_route("/gists/{id}/star"        , ec, ctx_51).methods({"PUT"});
        builder.add_route("/gists/{id}/star"        , ec, ctx_52).methods({"DELETE"});
        builder.add_route("/gists/{id}/star"        , ec, ctx_53).methods({"GET"});
        builder.add_route("/gists/{id}/forks"       , ec, ctx_54).methods({"POST"});
        builder.add_route("/gists/{id}"             , ec, ctx_55).methods({"DELETE"});

        // Git Data
        builder.add_route("/repos/{owner}/{repo}/git/blobs/{sha}"   , ec, ctx_56).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/git/blobs"         , ec, ctx_57).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/git/commits/{sha}" , ec, ctx_58).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/git/commits"       , ec, ctx_59).methods({"POST"});
        builder.add_route_prefix("/repos/{owner}/{repo}/git/refs/"  , ec, ctx_60).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/git/refs"          , ec, ctx_61).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/git/refs"          , ec, ctx_62).methods({"POST"});
        builder.add_route_prefix("/repos/{owner}/{repo}/git/refs/"  , ec, ctx_63).methods({"PATCH"});
        builder.add_route_prefix("/repos/{owner}/{repo}/git/refs/"  , ec, ctx_64).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/git/tags/{sha}"    , ec, ctx_65).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/git/tags"          , ec, ctx_66).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/git/trees/{sha}"   , ec, ctx_67).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/git/trees"         , ec, ctx_68).methods({"POST"});

        // Issues
        builder.add_route("/issues"                                             , ec, ctx_69).methods({"GET"});
        builder.add_route("/user/issues"                                        , ec, ctx_70).methods({"GET"});
        builder.add_route("/orgs/{org}/issues"                                  , ec, ctx_71).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues"                        , ec, ctx_72).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/comments"               , ec, ctx_73).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/comments/{id}"          , ec, ctx_74).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/events"                 , ec, ctx_75).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}"               , ec, ctx_76).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues"                        , ec, ctx_77).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}"               , ec, ctx_78).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/assignees"                     , ec, ctx_79).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/assignees/{assignee}"          , ec, ctx_80).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/comments"      , ec, ctx_81).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/comments"      , ec, ctx_82).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/issues/comments/{id}"          , ec, ctx_83).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/issues/comments/{id}"          , ec, ctx_84).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/events"        , ec, ctx_85).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/events/{id}"            , ec, ctx_86).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/labels"                        , ec, ctx_87).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/labels/{name}"                 , ec, ctx_88).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/labels"                        , ec, ctx_89).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/labels/{name}"                 , ec, ctx_90).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/labels/{name}"                 , ec, ctx_91).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/labels"        , ec, ctx_92).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/labels"        , ec, ctx_93).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/labels/{name}" , ec, ctx_94).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/labels"        , ec, ctx_95).methods({"PUT"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/labels"        , ec, ctx_96).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/milestones/{number}/labels"    , ec, ctx_97).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/milestones"                    , ec, ctx_98).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/milestones/{number}"           , ec, ctx_99).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/milestones"                    , ec, ctx_100).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/milestones/{number}"           , ec, ctx_101).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/milestones/{number}"           , ec, ctx_102).methods({"DELETE"});
    
        // Miscellaneous
        builder.add_route("/emojis"                     , ec, ctx_103).methods({"GET"});
        builder.add_route("/gitignore/templates"        , ec, ctx_104).methods({"GET"});
        builder.add_route("/gitignore/templates/{name}" , ec, ctx_105).methods({"GET"});
        builder.add_route("/markdown"                   , ec, ctx_106).methods({"POST"});
        builder.add_route("/markdown/raw"               , ec, ctx_107).methods({"POST"});
        builder.add_route("/meta"                       , ec, ctx_108).methods({"GET"});
        builder.add_route("/rate_limit"                 , ec, ctx_109).methods({"GET"});

        // Organizations
        builder.add_route("/users/{user}/orgs"                  , ec, ctx_110).methods({"GET"});
        builder.add_route("/user/orgs"                          , ec, ctx_111).methods({"GET"});
        builder.add_route("/orgs/{org}"                         , ec, ctx_112).methods({"GET"});
        builder.add_route("/orgs/{org}"                         , ec, ctx_113).methods({"PATCH"});
        builder.add_route("/orgs/{org}/members"                 , ec, ctx_114).methods({"GET"});
        builder.add_route("/orgs/{org}/members/{user}"          , ec, ctx_115).methods({"GET"});
        builder.add_route("/orgs/{org}/members/{user}"          , ec, ctx_116).methods({"DELETE"});
        builder.add_route("/orgs/{org}/public_members"          , ec, ctx_117).methods({"GET"});
        builder.add_route("/orgs/{org}/public_members/{user}"   , ec, ctx_118).methods({"GET"});
        builder.add_route("/orgs/{org}/public_members/{user}"   , ec, ctx_119).methods({"PUT"});
        builder.add_route("/orgs/{org}/public_members/{user}"   , ec, ctx_120).methods({"DELETE"});
        builder.add_route("/orgs/{org}/teams"                   , ec, ctx_121).methods({"GET"});
        builder.add_route("/teams/{id}"                         , ec, ctx_122).methods({"GET"});
        builder.add_route("/orgs/{org}/teams"                   , ec, ctx_123).methods({"POST"});
        builder.add_route("/teams/{id}"                         , ec, ctx_124).methods({"PATCH"});
        builder.add_route("/teams/{id}"                         , ec, ctx_125).methods({"DELETE"});
        builder.add_route("/teams/{id}/members"                 , ec, ctx_126).methods({"GET"});
        builder.add_route("/teams/{id}/members/{user}"          , ec, ctx_127).methods({"GET"});
        builder.add_route("/teams/{id}/members/{user}"          , ec, ctx_128).methods({"PUT"});
        builder.add_route("/teams/{id}/members/{user}"          , ec, ctx_129).methods({"DELETE"});
        builder.add_route("/teams/{id}/repos"                   , ec, ctx_130).methods({"GET"});
        builder.add_route("/teams/{id}/repos/{owner}/{repo}"    , ec, ctx_131).methods({"GET"});
        builder.add_route("/teams/{id}/repos/{owner}/{repo}"    , ec, ctx_132).methods({"PUT"});
        builder.add_route("/teams/{id}/repos/{owner}/{repo}"    , ec, ctx_133).methods({"DELETE"});
        builder.add_route("/user/teams"                         , ec, ctx_134).methods({"GET"});


        // Pull Requests
        builder.add_route("/repos/{owner}/{repo}/pulls"                     , ec, ctx_135).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/comments"            , ec, ctx_136).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}"            , ec, ctx_137).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls"                     , ec, ctx_138).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}"            , ec, ctx_139).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}/commits"    , ec, ctx_140).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}/files"      , ec, ctx_141).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}/merge"      , ec, ctx_142).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}/merge"      , ec, ctx_143).methods({"PUT"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}/comments"   , ec, ctx_144).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/comments/{number}"   , ec, ctx_145).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}/comments"   , ec, ctx_146).methods({"PUT"});
        builder.add_route("/repos/{owner}/{repo}/pulls/comments/{number}"   , ec, ctx_147).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/pulls/comments/{number}"   , ec, ctx_148).methods({"DELETE"});

        // Repositories
        builder.add_route("/user/repos"                                 , ec, ctx_149).methods({"GET"});
        builder.add_route("/users/{user}/repos"                         , ec, ctx_150).methods({"GET"});
        builder.add_route("/orgs/{org}/repos"                           , ec, ctx_151).methods({"GET"});
        builder.add_route("/repositories"                               , ec, ctx_152).methods({"GET"});
        builder.add_route("/user/repos"                                 , ec, ctx_153).methods({"POST"});
        builder.add_route("/orgs/{org}/repos"                           , ec, ctx_154).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}"                       , ec, ctx_155).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}"                       , ec, ctx_156).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/contributors"          , ec, ctx_157).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/languages"             , ec, ctx_158).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/teams"                 , ec, ctx_159).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/tags"                  , ec, ctx_160).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/branches"              , ec, ctx_161).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/branches/{branch}"     , ec, ctx_162).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}"                       , ec, ctx_163).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/collaborators"         , ec, ctx_164).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/collaborators/{user}"  , ec, ctx_165).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/collaborators/{user}"  , ec, ctx_166).methods({"PUT"});
        builder.add_route("/repos/{owner}/{repo}/collaborators/{user}"  , ec, ctx_167).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/comments"              , ec, ctx_168).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/commits/{sha}/comments", ec, ctx_169).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/commits/{sha}/comments", ec, ctx_170).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/comments/{id}"         , ec, ctx_171).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/comments/{id}"         , ec, ctx_172).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/comments/{id}"         , ec, ctx_173).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/commits"               , ec, ctx_174).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/commits/{sha}"         , ec, ctx_175).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/readme"                , ec, ctx_176).methods({"GET"});
        builder.add_route_prefix("/repos/{owner}/{repo}/contents/"      , ec, ctx_177).methods({"GET"});
        builder.add_route_prefix("/repos/{owner}/{repo}/contents/"      , ec, ctx_178).methods({"PUT"});
        builder.add_route_prefix("/repos/{owner}/{repo}/contents/"      , ec, ctx_179).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/keys/{id}"             , ec, ctx_180).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/downloads/{id}"        , ec, ctx_181).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/hooks/{id}"            , ec, ctx_182).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/releases/{id}"         , ec, ctx_183).methods({"GET"});

        builder.add_route("/repos/{owner}/{repo}/stats/contributors"    , ec, ctx_184).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/stats/commit_activity" , ec, ctx_185).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/stats/code_frequency"  , ec, ctx_186).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/stats/participation"   , ec, ctx_187).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/stats/punch_card"      , ec, ctx_188).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/statuses/{ref}"        , ec, ctx_189).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/statuses/{ref}"        , ec, ctx_190).methods({"POST"});

        builder.add_route("/repos/{owner}/{repo}/{archive_format}/{ref}", ec, ctx_191).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/keys"                  , ec, ctx_192).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/keys"                  , ec, ctx_193).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/keys/{id}"             , ec, ctx_194).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/keys/{id}"             , ec, ctx_195).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/downloads"             , ec, ctx_196).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/downloads/{id}"        , ec, ctx_197).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/forks"                 , ec, ctx_198).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/forks"                 , ec, ctx_199).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/hooks"                 , ec, ctx_200).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/hooks"                 , ec, ctx_201).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/hooks/{id}"            , ec, ctx_202).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/hooks/{id}/tests"      , ec, ctx_203).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/hooks/{id}"            , ec, ctx_204).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/merges"                , ec, ctx_205).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/releases"              , ec, ctx_206).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/releases"              , ec, ctx_207).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/releases/{id}"         , ec, ctx_208).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/releases/{id}"         , ec, ctx_209).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/releases/{id}/assets"  , ec, ctx_210).methods({"GET"});


        // Search
        builder.add_route("/search/repositories"                                        , ec, ctx_211).methods({"GET"});
        builder.add_route("/search/code"                                                , ec, ctx_212).methods({"GET"});
        builder.add_route("/search/issues"                                              , ec, ctx_213).methods({"GET"});
        builder.add_route("/search/users"                                               , ec, ctx_214).methods({"GET"});
        builder.add_route("/legacy/issues/search/{owner}/{repository}/{state}/{keyword}", ec, ctx_215).methods({"GET"});
        builder.add_route("/legacy/repos/search/{keyword}"                              , ec, ctx_216).methods({"GET"});
        builder.add_route("/legacy/user/search/{keyword}"                               , ec, ctx_217).methods({"GET"});
        builder.add_route("/legacy/user/email/{email}"                                  , ec, ctx_218).methods({"GET"});


        // Users
        builder.add_route("/users/{user}"                           , ec, ctx_219).methods({"GET"});
        builder.add_route("/user"                                   , ec, ctx_220).methods({"GET"});
        builder.add_route("/user"                                   , ec, ctx_221).methods({"PATCH"});
        builder.add_route("/users"                                  , ec, ctx_222).methods({"GET"});
        builder.add_route("/user/emails"                            , ec, ctx_223).methods({"GET"});
        builder.add_route("/user/emails"                            , ec, ctx_224).methods({"POST"});
        builder.add_route("/user/emails"                            , ec, ctx_225).methods({"DELETE"});
        builder.add_route("/users/{user}/followers"                 , ec, ctx_226).methods({"GET"});
        builder.add_route("/user/followers"                         , ec, ctx_227).methods({"GET"});
        builder.add_route("/users/{user}/following"                 , ec, ctx_228).methods({"GET"});
        builder.add_route("/user/following"                         , ec, ctx_229).methods({"GET"});
        builder.add_route("/user/following/{user}"                  , ec, ctx_230).methods({"GET"});
        builder.add_route("/users/{user}/following/{target_user}"   , ec, ctx_231).methods({"GET"});
        builder.add_route("/user/following/{user}"                  , ec, ctx_232).methods({"PUT"});
        builder.add_route("/user/following/{user}"                  , ec, ctx_233).methods({"DELETE"});
        builder.add_route("/users/{user}/keys"                      , ec, ctx_234).methods({"GET"});
        builder.add_route("/user/keys"                              , ec, ctx_235).methods({"GET"});
        builder.add_route("/user/keys/{id}"                         , ec, ctx_236).methods({"GET"});
        builder.add_route("/user/keys"                              , ec, ctx_237).methods({"POST"});
        builder.add_route("/user/keys/{id}"                         , ec, ctx_238).methods({"PATCH"});
        builder.add_route("/user/keys/{id}"                         , ec, ctx_239).methods({"DELETE"});
        
        return builder.build(ec);
    }

    MOCK_FUNCTOR(ctx_1, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_2, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_3, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_4, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_5, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_6, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_7, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_8, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_9, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_10, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_11, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_12, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_13, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_14, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_15, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_16, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_17, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_18, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_19, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_20, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_21, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_22, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_23, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_24, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_25, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_26, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_27, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_28, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_29, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_30, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_31, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_32, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_33, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_34, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_35, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_36, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_37, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_38, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_39, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_40, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_41, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_42, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_43, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_44, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_45, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_46, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_47, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_48, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_49, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_50, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_51, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_52, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_53, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_54, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_55, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_56, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_57, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_58, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_59, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_60, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_61, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_62, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_63, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_64, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_65, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_66, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_67, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_68, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_69, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_70, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_71, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_72, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_73, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_74, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_75, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_76, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_77, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_78, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_79, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_80, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_81, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_82, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_83, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_84, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_85, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_86, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_87, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_88, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_89, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_90, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_91, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_92, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_93, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_94, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_95, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_96, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_97, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_98, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_99, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_100, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_101, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_102, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_103, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_104, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_105, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_106, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_107, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_108, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_109, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_110, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_111, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_112, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_113, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_114, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_115, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_116, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_117, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_118, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_119, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_120, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_121, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_122, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_123, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_124, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_125, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_126, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_127, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_128, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_129, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_130, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_131, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_132, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_133, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_134, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_135, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_136, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_137, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_138, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_139, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_140, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_141, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_142, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_143, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_144, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_145, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_146, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_147, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_148, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_149, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_150, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_151, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_152, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_153, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_154, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_155, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_156, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_157, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_158, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_159, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_160, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_161, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_162, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_163, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_164, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_165, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_166, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_167, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_168, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_169, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_170, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_171, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_172, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_173, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_174, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_175, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_176, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_177, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_178, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_179, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_180, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_181, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_182, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_183, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_184, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_185, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_186, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_187, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_188, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_189, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_190, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_191, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_192, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_193, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_194, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_195, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_196, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_197, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_198, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_199, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_200, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_201, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_202, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_203, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_204, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_205, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_206, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_207, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_208, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_209, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_210, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_211, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_212, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_213, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_214, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_215, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_216, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_217, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_218, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_219, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_220, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_221, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_222, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_223, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_224, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_225, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_226, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_227, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_228, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_229, void(const hyperoute::route_context&));

    MOCK_FUNCTOR(ctx_230, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_231, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_232, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_233, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_234, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_235, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_236, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_237, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_238, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(ctx_239, void(const hyperoute::route_context&));
    // clang-format on
};

BOOST_AUTO_TEST_SUITE(GithubApi)
    // clang-format off
    const auto test_backends = []() {
        return boost::unit_test::data::make({ "simple"                         , "hyperscan"                         , "boost" })
             ^ boost::unit_test::data::make({ hyperoute::backend::make_simple(), hyperoute::backend::make_hyperscan(), hyperoute::backend::make_boost() });
    };
    // clang-format on

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_1, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_1).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/authorizations");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_2, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_2).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "ezdezfezdezdezedezdezdze";
        });

        router->call("GET", "/authorizations/ezdezfezdezdezedezdezdze");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_3, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_3).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("POST", "/authorizations");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_4, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_4).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("client_id")->second == "ncjizhdezdmzedlkzmld";
        });

        router->call("PUT", "/authorizations/clients/ncjizhdezdmzedlkzmld");
    }


    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_5, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_5).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "cbdhicdsjldskldjzldje";
        });

        router->call("PATCH", "/authorizations/cbdhicdsjldskldjzldje");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_6, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_6).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "gzhfihezkldjzkldzed";
        });

        router->call("DELETE", "/authorizations/gzhfihezkldjzkldzed");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_7, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_7).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("client_id")->second == "cezfezdzedezdzsasa"
                && ctx.params.find("access_token")->second == "czefedqdegrsedsqderdgfdq";
        });

        router->call("GET", "/applications/cezfezdzedezdzsasa/tokens/czefedqdegrsedsqderdgfdq");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_8, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_8).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("client_id")->second == "dzefregresdegtfhgdrf";
        });

        router->call("DELETE", "/applications/dzefregresdegtfhgdrf/tokens");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_9, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_9).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("client_id")->second == "cregtrhdrsfedezghtyhgrfseghfgdsezjyftdr"
                && ctx.params.find("access_token")->second == "czgfezfrrehtrsefderytrdffredfhftdr";
        });

        router->call(
            "DELETE",
            "/applications/cregtrhdrsfedezghtyhgrfseghfgdsezjyftdr/tokens/czgfezfrrehtrsefderytrdffredfhftdr"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_10, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_10).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/events");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_11, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_11).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "frgsfdezfrsfdsdsgfs"
                && ctx.params.find("repo")->second == "cfeqdezsgfsdqfrsfdsqds";
        });

        router->call("GET", "/repos/frgsfdezfrsfdsdsgfs/cfeqdezsgfsdqfrsfdsqds/events");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_12, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_12).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "gregref65f4s3f56sf54s"
                && ctx.params.find("repo")->second == "fezfes5f4se3f5sdsd3s5cs";
        });

        router->call("GET", "/networks/gregref65f4s3f56sf54s/fezfes5f4se3f5sdsd3s5cs/events");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_13, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_13).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "frfsqfqhkezdlsqbjqkjdc6sd54ec6sf5s46";
        });

        router->call("GET", "/orgs/frfsqfqhkezdlsqbjqkjdc6sd54ec6sf5s46/events");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_14, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_14).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "cz6fe5z4defszf654se65s";
        });

        router->call("GET", "/users/cz6fe5z4defszf654se65s/received_events");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_15, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_15).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "ef5sef35s4f3s54sd54ef6s54sd54";
        });

        router->call("GET", "/users/ef5sef35s4f3s54sd54ef6s54sd54/received_events/public");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_16, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_16).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "fs6f5es4f6s5f4es6f54s6d5s4d6";
        });

        router->call("GET", "/users/fs6f5es4f6s5f4es6f54s6d5s4d6/events");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_17, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_17).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "c4z6ef54sf54s6d54s6d5sd14x";
        });

        router->call("GET", "/users/c4z6ef54sf54s6d54s6d5sd14x/events/public");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_18, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_18).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "zef6ez4f6ez5f4s65c4ds6c5s4dc"
                && ctx.params.find("org")->second == "z5d6d54ez6d54e65d46d5e46c5s1x6541x";
        });

        router->call(
            "GET",
            "/users/zef6ez4f6ez5f4s65c4ds6c5s4dc/events/orgs/z5d6d54ez6d54e65d46d5e46c5s1x6541x"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_19, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_19).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/feeds");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_20, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_20).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/notifications");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_21, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_21).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "cds6c5ez4c6ze5d46z5c1sd6c54zdc6"
                && ctx.params.find("repo")->second == "zdze4d6ze54sz6c54sc65s4c6ds5c46s5c4";
        });

        router->call(
            "GET",
            "/repos/cds6c5ez4c6ze5d46z5c1sd6c54zdc6/zdze4d6ze54sz6c54sc65s4c6ds5c46s5c4/notifications"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_22, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_22).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("PUT", "/notifications");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_23, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_23).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "cez6d5se46ze54s65c4zs6c54se"
                && ctx.params.find("repo")->second == "64ez6d54ze6d51s35z4d6ze5d4";
        });

        router->call("PUT", "/repos/cez6d5se46ze54s65c4zs6c54se/64ez6d54ze6d51s35z4d6ze5d4/notifications");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_24, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_24).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "cze16d5es4d6s5c1s5d4z";
        });

        router->call("GET", "/notifications/threads/cze16d5es4d6s5c1s5d4z");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_25, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_25).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "ce65ez4zd4zed4zdz4dzd";
        });

        router->call("PATCH", "/notifications/threads/ce65ez4zd4zed4zdz4dzd");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_26, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_26).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "cez6d5s46c5ze4dc6z5c";
        });

        router->call("GET", "/notifications/threads/cez6d5s46c5ze4dc6z5c/subscription");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_27, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_27).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "fez654de51sd5e1d";
        });

        router->call("PUT", "/notifications/threads/fez654de51sd5e1d/subscription");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_28, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_28).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "cze54es6d5z46d5z4d6z5d4z";
        });

        router->call("DELETE", "/notifications/threads/cze54es6d5z46d5z4d6z5d4z/subscription");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_29, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_29).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "czc655s4c6s54c6s5c16sx5s1x"
                && ctx.params.find("repo")->second == "csd65s1c65sz4c6ez5sc6s5c1sz6";
        });

        router->call("GET", "/repos/czc655s4c6s54c6s5c16sx5s1x/csd65s1c65sz4c6ez5sc6s5c1sz6/stargazers");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_30, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_30).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "gtrhtr6gtr84g6frg4";
        });

        router->call("GET", "/users/gtrhtr6gtr84g6frg4/starred");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_31, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_31).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/user/starred");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_32, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_32).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "frz6f5rz4f6z5f4654z6d54"
                && ctx.params.find("repo")->second == "ze6d4zs6c6dv546f54s6";
        });

        router->call("GET", "/user/starred/frz6f5rz4f6z5f4654z6d54/ze6d4zs6c6dv546f54s6");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_33, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_33).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ezkjskjsldskmdsld"
                && ctx.params.find("repo")->second == "kfrksjdsmsdsemzjzldzkcjz";
        });

        router->call("PUT", "/user/starred/ezkjskjsldskmdsld/kfrksjdsmsdsemzjzldzkcjz");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_34, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_34).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "zefezdze6d5ze46zez5ez4"
                && ctx.params.find("repo")->second == "bhbf6bb65rt4gege6dv5re4ge";
        });

        router->call("DELETE", "/user/starred/zefezdze6d5ze46zez5ez4/bhbf6bb65rt4gege6dv5re4ge");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_35, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_35).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "dez6d54ze6+5ze4dc6zd54z"
                && ctx.params.find("repo")->second == "6ez54ezdez4d6ze5d46z5d46z5d1ze";
        });

        router->call("GET", "/repos/dez6d54ze6+5ze4dc6zd54z/6ez54ezdez4d6ze5d46z5d46z5d1ze/subscribers");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_36, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_36).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "fe1d6f5z4e6f5ez46ez546ze54dze65d4";
        });

        router->call("GET", "/users/fe1d6f5z4e6f5ez46ez546ze54dze65d4/subscriptions");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_37, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_37).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/user/subscriptions");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_38, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_38).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "czc65s4c6se54z6s54ez6c5zs"
                && ctx.params.find("repo")->second == "fv6sv54fd6v54df6v54df6v5d46v5df4v6d5v4";
        });

        router->call(
            "GET",
            "/repos/czc65s4c6se54z6s54ez6c5zs/fv6sv54fd6v54df6v54df6v5d46v5df4v6d5v4/subscription"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_39, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_39).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "vre6fr4f6er5gf4er6f54ref+"
                && ctx.params.find("repo")->second == "ef6s54f6zs5f4zf4zrf5z4f+z54fz65z4f";
        });

        router->call(
            "PUT",
            "/repos/vre6fr4f6er5gf4er6f54ref+/ef6s54f6zs5f4zf4zrf5z4f+z54fz65z4f/subscription"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_40, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_40).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "verg6r54v65f4r654d654e+"
                && ctx.params.find("repo")->second == "vsd6v54ff6r54f6re5f46e54c+z54fz65z4f";
        });

        router->call(
            "DELETE",
            "/repos/verg6r54v65f4r654d654e+/vsd6v54ff6r54f6re5f46e54c+z54fz65z4f/subscription"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_41, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_41).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "zf54z6f5z4f6ze54d6ez5d4ze+"
                && ctx.params.find("repo")->second == "vze46zs46ze54ez654ze6d54ezf5z4fz+z54fz65z4f";
        });

        router->call(
            "GET",
            "/user/subscriptions/zf54z6f5z4f6ze54d6ez5d4ze+/vze46zs46ze54ez654ze6d54ezf5z4fz+z54fz65z4f"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_42, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_42).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "fre65r4f6rf54ezr6f5e4f6ez5f4ez+"
                && ctx.params.find("repo")->second == "gtg7r6g5r4gref4erf4ezf4zefz6f4z+z54fz65z4f";
        });

        router->call(
            "PUT",
            "/user/subscriptions/fre65r4f6rf54ezr6f5e4f6ez5f4ez+/gtg7r6g5r4gref4erf4ezf4zefz6f4z+z54fz65z4f"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_43, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_43).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "er6g54df6gdr46g5r46f5r4f+4f+se4+"
                && ctx.params.find("repo")->second == "5ffd6v5fd46er5g46r5f4e6f546f5e4c651";
        });

        router->call(
            "DELETE",
            "/user/subscriptions/er6g54df6gdr46g5r46f5r4f+4f+se4+/5ffd6v5fd46er5g46r5f4e6f546f5e4c651"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_44, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_44).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "fr6f5rf6e5f1ze6f51ezf6ze51";
        });

        router->call("GET", "/users/fr6f5rf6e5f1ze6f51ezf6ze51/gists");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_45, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_45).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/gists");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_46, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_46).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/gists/public");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_47, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_47).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/gists/starred");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_48, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_48).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "vr6f54r6f5er4f6er5f4e6fr54";
        });

        router->call("GET", "/gists/vr6f54r6f5er4f6er5f4e6fr54");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_49, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_49).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("POST", "/gists");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_50, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_50).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "c6z5z6f5ez4f65ze46ze54dz6e5d4ze65";
        });

        router->call("PATCH", "/gists/c6z5z6f5ez4f65ze46ze54dz6e5d4ze65");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_51, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_51).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "er6f5rze4f6ze5d46ez5d4ze6f54ze6";
        });

        router->call("PUT", "/gists/er6f5rze4f6ze5d46ez5d4ze6f54ze6/star");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_52, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_52).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "zfrz4f6z5f4z6f54erz6f";
        });

        router->call("DELETE", "/gists/zfrz4f6z5f4z6f54erz6f/star");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_53, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_53).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "1z6f51ez651ze651zed65z1";
        });

        router->call("GET", "/gists/1z6f51ez651ze651zed65z1/star");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_54, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_54).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "fref65zref46zefez6f54ze6f4ze6fz";
        });

        router->call("POST", "/gists/fref65zref46zefez6f54ze6f4ze6fz/forks");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_55, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_55).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "ef4zf6ze5f6zefczfez6z46";
        });

        router->call("DELETE", "/gists/ef4zf6ze5f6zefczfez6z46");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_56, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_56).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ezesfsfscs6c5s4c6s54"
                && ctx.params.find("repo")->second == "ze65d4e6d54ezd65ez4d6e5f46s5v4s65v4sd6fz5"
                && ctx.params.find("sha")->second == "vze6f54sef65ez4f6zs5f4z65d4se6d5se465";
        });

        router->call(
            "GET",
            "/repos/ezesfsfscs6c5s4c6s54/ze65d4e6d54ezd65ez4d6e5f46s5v4s65v4sd6fz5/git/blobs/"
            "vze6f54sef65ez4f6zs5f4z65d4se6d5se465"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_57, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_57).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "fr6f5rs4f6s5f46zf54zfze54"
                && ctx.params.find("repo")->second == "ezf65ez46z54ze6d54s6e5s4dzs6";
        });

        router->call("POST", "/repos/fr6f5rs4f6s5f46zf54zfze54/ezf65ez46z54ze6d54s6e5s4dzs6/git/blobs");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_58, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_58).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "6546f4s6f4s6c54s68s4c6z84cd6z5c4sd"
                && ctx.params.find("repo")->second == "sd65ds46sd5c4sd6c4s68d4s6"
                && ctx.params.find("sha")->second == "cds654s6f5es1d6s5d1x68sd4x";
        });

        router->call(
            "GET",
            "/repos/6546f4s6f4s6c54s68s4c6z84cd6z5c4sd/sd65ds46sd5c4sd6c4s68d4s6/git/commits/"
            "cds654s6f5es1d6s5d1x68sd4x"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_59, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_59).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "dez6d5zed46sz5dcs6cd5cze"
                && ctx.params.find("repo")->second == "re6g54fd13c5e4f6csq";
        });

        router->call("POST", "/repos/dez6d5zed46sz5dcs6cd5cze/re6g54fd13c5e4f6csq/git/commits");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_60, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_60).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "frzfpoljkhjnbcx6"
                && ctx.params.find("repo")->second == "ujghfgt4vfd5g4vdr5fe"
                && ctx.remaining_path == "fgers6f5rsf13f5r4";
        });

        router->call("GET", "/repos/frzfpoljkhjnbcx6/ujghfgt4vfd5g4vdr5fe/git/refs/fgers6f5rsf13f5r4");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_61, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_61).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "gtergr8e4fr5f4ez64"
                && ctx.params.find("repo")->second == "hthfgtf6g54bf65tdg4de6";
        });

        router->call("GET", "/repos/gtergr8e4fr5f4ez64/hthfgtf6g54bf65tdg4de6/git/refs");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_62, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_62).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ntyrgtd84dfv35fd4v6s5c4"
                && ctx.params.find("repo")->second == "rh6tgfd4gd5f4ds6f54f6s5c4";
        });

        router->call("POST", "/repos/ntyrgtd84dfv35fd4v6s5c4/rh6tgfd4gd5f4ds6f54f6s5c4/git/refs");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_63, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_63).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "gerg65rd4fsz5f4ez6dz54"
                && ctx.params.find("repo")->second == "vfr6r5f4ez3d54ze6f5zfze4"
                && ctx.remaining_path
                       == "ukyt9hf4gdf6g5vt4dh68dg4f6d+rdh5t4dgdrg54erdg65drfg4d6+tghds6g5fre4sfsr5f46rsf54s";
        });

        router->call(
            "PATCH",
            "/repos/gerg65rd4fsz5f4ez6dz54/vfr6r5f4ez3d54ze6f5zfze4/git/refs/"
            "ukyt9hf4gdf6g5vt4dh68dg4f6d+rdh5t4dgdrg54erdg65drfg4d6+tghds6g5fre4sfsr5f46rsf54s"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_64, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_64).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ntdh4gedrsgf4zr6f54ze6"
                && ctx.params.find("repo")->second == "yyjuykjgf4bd654fr65f4z65f4"
                && ctx.remaining_path == "yhtedf54nhd+uytjhyf4h6b5d4gfs+kaed65ds4v6dh4ukj4g6f";
        });

        router->call(
            "DELETE",
            "/repos/ntdh4gedrsgf4zr6f54ze6/yyjuykjgf4bd654fr65f4z65f4/git/refs/"
            "yhtedf54nhd+uytjhyf4h6b5d4gfs+kaed65ds4v6dh4ukj4g6f"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_65, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_65).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ger6f5s5z1d6z5d1ze6d51z6d5z1d6z51d"
                && ctx.params.find("repo")->second == "trhgdf4f6s5cze6d5ze1d6ze5d4z6"
                && ctx.params.find("sha")->second == "htegf6s54szf5erz6f5ez46dz5sd4z";
        });

        router->call(
            "GET",
            "/repos/ger6f5s5z1d6z5d1ze6d51z6d5z1d6z51d/trhgdf4f6s5cze6d5ze1d6ze5d4z6/git/tags/"
            "htegf6s54szf5erz6f5ez46dz5sd4z"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_66, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_66).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "thegfrsrf6r5g46dr5g4r65f4e6c5s4x6qs5"
                && ctx.params.find("repo")->second == "yugkhgfgv4s6c5d4c6s51xs651";
        });

        router->call(
            "POST",
            "/repos/thegfrsrf6r5g46dr5g4r65f4e6c5s4x6qs5/yugkhgfgv4s6c5d4c6s51xs651/git/tags"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_67, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_67).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "wqsf6ds54df65h6k5g4fvdcsx"
                && ctx.params.find("repo")->second == "bfgsedqd65ds4g6d54ytjh4gd6sd1s32f1s"
                && ctx.params.find("sha")->second == "polkj6ghh5h4yf6h5gdr6sf5d4q1";
        });

        router->call(
            "GET",
            "/repos/wqsf6ds54df65h6k5g4fvdcsx/bfgsedqd65ds4g6d54ytjh4gd6sd1s32f1s/git/trees/"
            "polkj6ghh5h4yf6h5gdr6sf5d4q1"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_68, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_68).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "dgtrjhdf54se65td4hg6d5s1cs651"
                && ctx.params.find("repo")->second == "lkjuygfhgd4f6s4fs654s6x54s";
        });

        router->call("POST", "/repos/dgtrjhdf54se65td4hg6d5s1cs651/lkjuygfhgd4f6s4fs654s6x54s/git/trees");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_69, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_69).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/issues");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_70, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_70).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/user/issues");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_71, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_71).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "tej6hftd4gfgef5";
        });

        router->call("GET", "/orgs/tej6hftd4gfgef5/issues");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_72, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_72).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "tffh8et4dg6er5f4efz4dz4"
                && ctx.params.find("repo")->second == "trgefzrf6z5d4z6fd5z4d6z5d4";
        });

        router->call("GET", "/repos/tffh8et4dg6er5f4efz4dz4/trgefzrf6z5d4z6fd5z4d6z5d4/issues");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_73, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_73).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "t6he5g46erfez46d5z4"
                && ctx.params.find("repo")->second == "berfez68d4edz6d8z";
        });

        router->call("GET", "/repos/t6he5g46erfez46d5z4/berfez68d4edz6d8z/issues/comments");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_74, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_74).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "354f6zed4z6xz84dz6"
                && ctx.params.find("repo")->second == "fe6zf54ez6d5z4x6zd4z6"
                && ctx.params.find("id")->second == "65r7g6z5s4d6ezd4ze6dz5d4";
        });

        router->call(
            "GET",
            "/repos/354f6zed4z6xz84dz6/fe6zf54ez6d5z4x6zd4z6/issues/comments/65r7g6z5s4d6ezd4ze6dz5d4"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_75, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_75).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "f6r5zf4x651z6dz54dez"
                && ctx.params.find("repo")->second == "f4s65ed41zx6zd4";
        });

        router->call("GET", "/repos/f6r5zf4x651z6dz54dez/f4s65ed41zx6zd4/issues/events");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_76, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_76).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "684jk6y54jh6tg4rv64"
                && ctx.params.find("repo")->second == "46tgedfg4fd654csd6c5s4"
                && ctx.params.find("number")->second == "tyjrgf6sc4sz6cs5zdz4d";
        });

        router->call("GET", "/repos/684jk6y54jh6tg4rv64/46tgedfg4fd654csd6c5s4/issues/tyjrgf6sc4sz6cs5zdz4d");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_77, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_77).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "6hf5v4dr6se54dcz6d5z4d"
                && ctx.params.find("repo")->second == "dcezd5az4d6az5d4az6da5";
        });

        router->call("POST", "/repos/6hf5v4dr6se54dcz6d5z4d/dcezd5az4d6az5d4az6da5/issues");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_78, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_78).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "rgre6f54ze6dze5d4z6e54"
                && ctx.params.find("repo")->second == "tbet5f4rz3f5ze4fze54"
                && ctx.params.find("number")->second == "fre65f46f5z4d6z5d4zedze6d54";
        });

        router->call(
            "PATCH",
            "/repos/rgre6f54ze6dze5d4z6e54/tbet5f4rz3f5ze4fze54/issues/fre65f46f5z4d6z5d4zedze6d54"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_79, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_79).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "g5er4g6zf54zf6z5d4z6"
                && ctx.params.find("repo")->second == "65h4rt6g54ref65ef4ez6d54";
        });

        router->call("GET", "/repos/g5er4g6zf54zf6z5d4z6/65h4rt6g54ref65ef4ez6d54/assignees");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_80, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_80).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "rgrzf54ze6dez5d4ze6d5z"
                && ctx.params.find("repo")->second == "rhrezfez54d3d1z6d54"
                && ctx.params.find("assignee")->second == "herf6ez4d6ze4zed6x5";
        });

        router->call(
            "GET",
            "/repos/rgrzf54ze6dez5d4ze6d5z/rhrezfez54d3d1z6d54/assignees/herf6ez4d6ze4zed6x5"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_81, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_81).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "hkijg65fb4vfd6gdf5f4d6"
                && ctx.params.find("repo")->second == "trjh6etr5df4ze6f5ezf4ze6d5z4"
                && ctx.params.find("number")->second == "yrhtge6r5f4zedzdz6eed5ze";
        });

        router->call(
            "GET",
            "/repos/hkijg65fb4vfd6gdf5f4d6/trjh6etr5df4ze6f5ezf4ze6d5z4/issues/yrhtge6r5f4zedzdz6eed5ze/"
            "comments"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_82, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_82).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "35rsg46z5d4ze6d5z4dz6d54zd"
                && ctx.params.find("repo")->second == "54r3f54f3z5d4ez6d5ez4d6"
                && ctx.params.find("number")->second == "6d5f4654a6d4za6d54za3s5az4";
        });

        router->call(
            "POST",
            "/repos/35rsg46z5d4ze6d5z4dz6d54zd/54r3f54f3z5d4ez6d5ez4d6/issues/6d5f4654a6d4za6d54za3s5az4/"
            "comments"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_83, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_83).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "65e4f6z5d4ez6d54z654"
                && ctx.params.find("repo")->second == "zeds65e465ed4x3z8d4"
                && ctx.params.find("id")->second == "qe5d4z6d54zd6zd46zd4zs";
        });

        router->call(
            "PATCH",
            "/repos/65e4f6z5d4ez6d54z654/zeds65e465ed4x3z8d4/issues/comments/qe5d4z6d54zd6zd46zd4zs"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_84, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_84).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "65ef4zed5z1s6z5d4z65"
                && ctx.params.find("repo")->second == "54zfr1d3z5ed13z5ed1z5d1"
                && ctx.params.find("id")->second == "c1x65zd1z5d3daszd6zad";
        });

        router->call(
            "DELETE",
            "/repos/65ef4zed5z1s6z5d4z65/54zfr1d3z5ed13z5ed1z5d1/issues/comments/c1x65zd1z5d3daszd6zad"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_85, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_85).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "5z6ef54x6zd543s5as"
                && ctx.params.find("repo")->second == "sf54z6d5z4ed651d6w51zs"
                && ctx.params.find("number")->second == "zdxz6ed5z4edzx684zd";
        });

        router->call(
            "GET",
            "/repos/5z6ef54x6zd543s5as/sf54z6d5z4ed651d6w51zs/issues/zdxz6ed5z4edzx684zd/events"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_86, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_86).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "dezdfze65d4e"
                && ctx.params.find("repo")->second == "ez6d8ed41xz6ed8ez"
                && ctx.params.find("id")->second == "fz6efd4x1ze6sf8zed4z";
        });

        router->call("GET", "/repos/dezdfze65d4e/ez6d8ed41xz6ed8ez/issues/events/fz6efd4x1ze6sf8zed4z");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_87, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_87).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "zf65d1z6e5d1zx65"
                && ctx.params.find("repo")->second == "fezd51ze6dze41d6zed4";
        });

        router->call("GET", "/repos/zf65d1z6e5d1zx65/fezd51ze6dze41d6zed4/labels");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_88, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_88).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "3s5f4s65ezc84"
                && ctx.params.find("repo")->second == "fze6f4ef6ez8f4ze6f8e4"
                && ctx.params.find("name")->second == "fe6zf54ez6f84ez6fze+";
        });

        router->call("GET", "/repos/3s5f4s65ezc84/fze6f4ef6ez8f4ze6f8e4/labels/fe6zf54ez6f84ez6fze+");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_89, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_89).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "3s5f4s65ezc84"
                && ctx.params.find("repo")->second == "fze6f4ef6ez8f4ze6f8e4";
        });

        router->call("POST", "/repos/3s5f4s65ezc84/fze6f4ef6ez8f4ze6f8e4/labels");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_90, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_90).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "6d5f4z68ed46z8d4z"
                && ctx.params.find("repo")->second == "65sf468c468ez46dez84d"
                && ctx.params.find("name")->second == "65zed416ze8d46z8d4ez";
        });

        router->call("PATCH", "/repos/6d5f4z68ed46z8d4z/65sf468c468ez46dez84d/labels/65zed416ze8d46z8d4ez");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_91, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_91).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "z6f54d1z6x8zd46ez"
                && ctx.params.find("repo")->second == "3e5f4dze6d841ze6d8ze4"
                && ctx.params.find("name")->second == "e2f4ezd6ze4dz5de";
        });

        router->call("DELETE", "/repos/z6f54d1z6x8zd46ez/3e5f4dze6d841ze6d8ze4/labels/e2f4ezd6ze4dz5de");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_92, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_92).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "65zef4d6z8d4z6d84edz68"
                && ctx.params.find("repo")->second == "fzr64c16e84cd1z6z8d4"
                && ctx.params.find("number")->second == "zf68z4d1x6z8ed4z6d8z4";
        });

        router->call(
            "GET",
            "/repos/65zef4d6z8d4z6d84edz68/fzr64c16e84cd1z6z8d4/issues/zf68z4d1x6z8ed4z6d8z4/labels"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_93, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_93).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "sef684dz6d8ez1dz6z4"
                && ctx.params.find("repo")->second == "6fe5z4d1x6zd84zd6az84ds"
                && ctx.params.find("number")->second == "ze5f4d1z6d81ez6dz";
        });

        router->call(
            "POST",
            "/repos/sef684dz6d8ez1dz6z4/6fe5z4d1x6zd84zd6az84ds/issues/ze5f4d1z6d81ez6dz/labels"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_94, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_94).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "6z5d41z6d84ze1d6z5d4"
                && ctx.params.find("repo")->second == "65e4d16zd851ez6d5ez1dz"
                && ctx.params.find("number")->second == "65ezd16zed8541ez6dz4"
                && ctx.params.find("name")->second == "ze6f5d41z68ez1dz5d1z6e";
        });

        router->call(
            "DELETE",
            "/repos/6z5d41z6d84ze1d6z5d4/65e4d16zd851ez6d5ez1dz/issues/65ezd16zed8541ez6dz4/labels/"
            "ze6f5d41z68ez1dz5d1z6e"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_95, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_95).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "f6z5ef416dz5e1d6zd5ze"
                && ctx.params.find("repo")->second == "6e5zf4d61ez8d416zed84z6d"
                && ctx.params.find("number")->second == "24qD6z8dzed65zed6z5ed";
        });

        router->call(
            "PUT",
            "/repos/f6z5ef416dz5e1d6zd5ze/6e5zf4d61ez8d416zed84z6d/issues/24qD6z8dzed65zed6z5ed/labels"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_96, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_96).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "65z1d6ez8d1z65d46ze5"
                && ctx.params.find("repo")->second == "651d6ez8d4e6zd4ez6d4z6d54ezd"
                && ctx.params.find("number")->second == "1x586x1zdz8d51010";
        });

        router->call(
            "DELETE",
            "/repos/65z1d6ez8d1z65d46ze5/651d6ez8d4e6zd4ez6d4z6d54ezd/issues/1x586x1zdz8d51010/labels"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_97, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_97).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "089z1e5ez6c10dz541dez"
                && ctx.params.find("repo")->second == "216d51d06z5d1z6d5zs20w"
                && ctx.params.find("number")->second == "c51z8ez9d54x1z51dxez6dz";
        });

        router->call(
            "GET",
            "/repos/089z1e5ez6c10dz541dez/216d51d06z5d1z6d5zs20w/milestones/c51z8ez9d54x1z51dxez6dz/labels"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_98, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_98).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "351z6dez1daed46ezd54zedz5d4"
                && ctx.params.find("repo")->second == "c32z1d9ze8d16z5d4zedze4";
        });

        router->call("GET", "/repos/351z6dez1daed46ezd54zedz5d4/c32z1d9ze8d16z5d4zedze4/milestones");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_99, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_99).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "cd4z198z1cz68d4ezd84zx18z9"
                && ctx.params.find("repo")->second == "6cz4d69ze8d4ze6d18ez4dze8d4ze98"
                && ctx.params.find("number")->second == "6c5z16c8ez1d6ez5x1z65d4ez6d56z";
        });

        router->call(
            "GET",
            "/repos/cd4z198z1cz68d4ezd84zx18z9/6cz4d69ze8d4ze6d18ez4dze8d4ze98/milestones/"
            "6c5z16c8ez1d6ez5x1z65d4ez6d56z"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_100, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_100).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "d6ez51d6ze8d4e6d546ze5d4ze6d4"
                && ctx.params.find("repo")->second == "059ez5z65ed41z6de8z4ed";
        });

        router->call("POST", "/repos/d6ez51d6ze8d4e6d546ze5d4ze6d4/059ez5z65ed41z6de8z4ed/milestones");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_101, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_101).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "6d5ez1dez86d4e6zd516dz46ed8z1"
                && ctx.params.find("repo")->second == "31d6zd841ze6d84zd6ze5d4"
                && ctx.params.find("number")->second == "ljk6ki1n6uyg8jh4ftg6v84";
        });

        router->call(
            "PATCH",
            "/repos/6d5ez1dez86d4e6zd516dz46ed8z1/31d6zd841ze6d84zd6ze5d4/milestones/ljk6ki1n6uyg8jh4ftg6v84"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_102, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_102).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "6iuyjh4g1vdfs8c4xds6"
                && ctx.params.find("repo")->second == "frehgerf84c1ds6c8ds"
                && ctx.params.find("number")->second == "0e59da8d4x6a5d4z6ed54d6d5";
        });

        router->call(
            "DELETE",
            "/repos/6iuyjh4g1vdfs8c4xds6/frehgerf84c1ds6c8ds/milestones/0e59da8d4x6a5d4z6ed54d6d5"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_103, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_103).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/emojis");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_104, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_104).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/gitignore/templates");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_105, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_105).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("name")->second == "5rf1zd84zed41e6za";
        });

        router->call("GET", "/gitignore/templates/5rf1zd84zed41e6za");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_106, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_106).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("POST", "/markdown");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_107, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_107).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("POST", "/markdown/raw");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_108, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_108).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/meta");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_109, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_109).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/rate_limit");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_110, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_110).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "f8za6d51c6f514ez6d5ze1d";
        });

        router->call("GET", "/users/f8za6d51c6f514ez6d5ze1d/orgs");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_111, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_111).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/user/orgs");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_112, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_112).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "iuythf6gvfd51c6sf8ez";
        });

        router->call("GET", "/orgs/iuythf6gvfd51c6sf8ez");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_113, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_113).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "kijytfdgv6fdxv81ds0";
        });

        router->call("PATCH", "/orgs/kijytfdgv6fdxv81ds0");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_114, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_114).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "iuytr6gdvf81sfzde6d5zd4";
        });

        router->call("GET", "/orgs/iuytr6gdvf81sfzde6d5zd4/members");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_115, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_115).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "wxdf16zr8d4ez1qd0ezd6e41"
                && ctx.params.find("user")->second == "nbrte9tf84er1scre9r8f6re410";
        });

        router->call("GET", "/orgs/wxdf16zr8d4ez1qd0ezd6e41/members/nbrte9tf84er1scre9r8f6re410");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_116, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_116).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "b1ver9sf8cx1zdx0z6"
                && ctx.params.find("user")->second == "pok1jb6f8cg41vceds0c6dz51";
        });

        router->call("DELETE", "/orgs/b1ver9sf8cx1zdx0z6/members/pok1jb6f8cg41vceds0c6dz51");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_117, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_117).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "v1rz6f8d4xz1ef6d8ez4ed";
        });

        router->call("GET", "/orgs/v1rz6f8d4xz1ef6d8ez4ed/public_members");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_118, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_118).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "hg1evfcd6r8f1c0zds"
                && ctx.params.find("user")->second == "gzrd1exz9dez84d1xzd98ez64";
        });

        router->call("GET", "/orgs/hg1evfcd6r8f1c0zds/public_members/gzrd1exz9dez84d1xzd98ez64");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_119, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_119).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "y6juh8ge4fc1re986f4re1sf6re84"
                && ctx.params.find("user")->second == "jytr6thgvre1f6dezd16ezd4";
        });

        router->call("PUT", "/orgs/y6juh8ge4fc1re986f4re1sf6re84/public_members/jytr6thgvre1f6dezd16ezd4");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_120, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_120).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "trheg6f5re1fcz6fr8ez4"
                && ctx.params.find("user")->second == "byrvfr1zf89erf4rez";
        });

        router->call("DELETE", "/orgs/trheg6f5re1fcz6fr8ez4/public_members/byrvfr1zf89erf4rez");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_121, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_121).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "gnhbvrezx9e4ffzd469z8d4e";
        });

        router->call("GET", "/orgs/gnhbvrezx9e4ffzd469z8d4e/teams");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_122, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_122).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "fregf4dcze19d86x41ez6dezd4ze";
        });

        router->call("GET", "/teams/fregf4dcze19d86x41ez6dezd4ze");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_123, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_123).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "huhtrgfdbv9gr8d4gf";
        });

        router->call("POST", "/orgs/huhtrgfdbv9gr8d4gf/teams");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_124, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_124).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "rt68f4r198f4re6f84ref86e4";
        });

        router->call("PATCH", "/teams/rt68f4r198f4re6f84ref86e4");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_125, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_125).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "yruytge798re4f1e";
        });

        router->call("DELETE", "/teams/yruytge798re4f1e");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_126, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_126).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "6r54f1cz968d4ze1dx";
        });

        router->call("GET", "/teams/6r54f1cz968d4ze1dx/members");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_127, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_127).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "z6r8f4c1exz6dez41d"
                && ctx.params.find("user")->second == "rgs6fc8z41dxez68qd4ez";
        });

        router->call("GET", "/teams/z6r8f4c1exz6dez41d/members/rgs6fc8z41dxez68qd4ez");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_128, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_128).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "kj4hbr9d86fg4vcefdf68er4zdx"
                && ctx.params.find("user")->second == "ao6ijh5b4vd1xc06xr5wf4";
        });

        router->call("PUT", "/teams/kj4hbr9d86fg4vcefdf68er4zdx/members/ao6ijh5b4vd1xc06xr5wf4");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_129, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_129).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "y3gv4cds19f68ez4d1z"
                && ctx.params.find("user")->second == "tf2hygv4fe19s68c41sfcre6f8d4";
        });

        router->call("DELETE", "/teams/y3gv4cds19f68ez4d1z/members/tf2hygv4fe19s68c41sfcre6f8d4");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_130, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_130).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "dzf35c1ze6d8ez41dez654";
        });

        router->call("GET", "/teams/dzf35c1ze6d8ez41dez654/repos");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_131, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_131).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "t4eg6fr84f6re8f4erf"
                && ctx.params.find("owner")->second == "zf65dez1d6ez8d4xez"
                && ctx.params.find("repo")->second == "ijhr6tdf84ce6sf8c4sf6d84";
        });

        router->call("GET", "/teams/t4eg6fr84f6re8f4erf/repos/zf65dez1d6ez8d4xez/ijhr6tdf84ce6sf8c4sf6d84");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_132, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_132).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "trhgfre46t8f4re16sf8r4"
                && ctx.params.find("owner")->second == "jyt6fdg4res6fc8ezd4"
                && ctx.params.find("repo")->second == "bytr6gef8dez4d6ez8dze4s";
        });

        router->call(
            "PUT",
            "/teams/trhgfre46t8f4re16sf8r4/repos/jyt6fdg4res6fc8ezd4/bytr6gef8dez4d6ez8dze4s"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_133, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_133).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "kjth6rdfv8c4d"
                && ctx.params.find("owner")->second == "nrtegrf68r4zffr8e6f4"
                && ctx.params.find("repo")->second == "wer6hgfre4zdze6";
        });

        router->call("DELETE", "/teams/kjth6rdfv8c4d/repos/nrtegrf68r4zffr8e6f4/wer6hgfre4zdze6");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_134, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_134).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/user/teams");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_135, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_135).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "y6ghrgd4c1e6g8re4rf6re8"
                && ctx.params.find("repo")->second == "yrh5g41er6sf4ez6d54xez6d54ze";
        });

        router->call("GET", "/repos/y6ghrgd4c1e6g8re4rf6re8/yrh5g41er6sf4ez6d54xez6d54ze/pulls");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_136, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_136).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "trhegs6fedc84rs1fre6"
                && ctx.params.find("repo")->second == "rddtgfc6sd4c1res6f8";
        });

        router->call("GET", "/repos/trhegs6fedc84rs1fre6/rddtgfc6sd4c1res6f8/pulls/comments");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_137, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_137).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "tdgfre5sf41cre5sf4ezze5d4"
                && ctx.params.find("repo")->second == "tdgf6r8zs4fc6es8f4cre6sf84"
                && ctx.params.find("number")->second == "bver5zf7chtrdg5fvresfd";
        });

        router->call(
            "GET",
            "/repos/tdgfre5sf41cre5sf4ezze5d4/tdgf6r8zs4fc6es8f4cre6sf84/pulls/bver5zf7chtrdg5fvresfd"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_138, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_138).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "rthgv1fes68c4resfcd6sc4d"
                && ctx.params.find("repo")->second == "yjhrgesfd6x84eces6f8";
        });

        router->call("POST", "/repos/rthgv1fes68c4resfcd6sc4d/yjhrgesfd6x84eces6f8/pulls");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_139, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_139).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "tegfcsdf6redgvefds6c84"
                && ctx.params.find("repo")->second == "ergytjhg6trd8fxg4cref"
                && ctx.params.find("number")->second == "tuhegsfefryjg9fh8b4";
        });

        router->call(
            "PATCH",
            "/repos/tegfcsdf6redgvefds6c84/ergytjhg6trd8fxg4cref/pulls/tuhegsfefryjg9fh8b4"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_140, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_140).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "trhgersgfresf6cre5f4"
                && ctx.params.find("repo")->second == "mlkjtbrvdfx6v5f4r"
                && ctx.params.find("number")->second == "yugj6h5b4gdg1v6ed8fg";
        });

        router->call(
            "GET",
            "/repos/trhgersgfresf6cre5f4/mlkjtbrvdfx6v5f4r/pulls/yugj6h5b4gdg1v6ed8fg/commits"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_141, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_141).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "oiuyhtrdrgf6c5f4vfd"
                && ctx.params.find("repo")->second == "nbrer1sfc6s8fc4e1sfcd"
                && ctx.params.find("number")->second == "versfcsfc84re1sfc0e5sf";
        });

        router->call(
            "GET",
            "/repos/oiuyhtrdrgf6c5f4vfd/nbrer1sfc6s8fc4e1sfcd/pulls/versfcsfc84re1sfc0e5sf/files"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_142, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_142).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "turydgsrf4cz6fsc841dsf"
                && ctx.params.find("repo")->second == "btefrs6c8cesrgt1frd"
                && ctx.params.find("number")->second == "plkjhfd46vc5ds4";
        });

        router->call("GET", "/repos/turydgsrf4cz6fsc841dsf/btefrs6c8cesrgt1frd/pulls/plkjhfd46vc5ds4/merge");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_143, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_143).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "hbveczef6c54sf"
                && ctx.params.find("repo")->second == "aqfvtrf6thg5v4dgvr6d"
                && ctx.params.find("number")->second == "uytjufhgxvf1c68rs4f";
        });

        router->call("PUT", "/repos/hbveczef6c54sf/aqfvtrf6thg5v4dgvr6d/pulls/uytjufhgxvf1c68rs4f/merge");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_144, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_144).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "tehgsfcd864rersf1c"
                && ctx.params.find("repo")->second == "bvrtef68cr4esfcre6"
                && ctx.params.find("number")->second == "regsf6rdc41sfre5";
        });

        router->call("GET", "/repos/tehgsfcd864rersf1c/bvrtef68cr4esfcre6/pulls/regsf6rdc41sfre5/comments");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_145, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_145).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "jhrgd6fsf8c41fd"
                && ctx.params.find("repo")->second == "nbygrtegfdfrrzf"
                && ctx.params.find("number")->second == "aegt6dg8f4re1sfer6";
        });

        router->call("GET", "/repos/jhrgd6fsf8c41fd/nbygrtegfdfrrzf/pulls/comments/aegt6dg8f4re1sfer6");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_146, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_146).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ytrygdc16es8f4e"
                && ctx.params.find("repo")->second == "aerdcrsdf684xe1qd"
                && ctx.params.find("number")->second == "poyujtg5fcv4fd6f8ez4";
        });

        router->call("PUT", "/repos/ytrygdc16es8f4e/aerdcrsdf684xe1qd/pulls/poyujtg5fcv4fd6f8ez4/comments");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_147, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_147).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "uhrdc5esc"
                && ctx.params.find("repo")->second == "wfretf5er8gt4rerf6"
                && ctx.params.find("number")->second == "jloi6kj4uythbvr6dgv8fd4c";
        });

        router->call("PATCH", "/repos/uhrdc5esc/wfretf5er8gt4rerf6/pulls/comments/jloi6kj4uythbvr6dgv8fd4c");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_148, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_148).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "oiythf5gvfd4cre6sfce"
                && ctx.params.find("repo")->second == "freygfr46efd41ezd6ez8ff4e6"
                && ctx.params.find("number")->second == "juyghb6g8c4vfe1dfer57";
        });

        router->call(
            "DELETE",
            "/repos/oiythf5gvfd4cre6sfce/freygfr46efd41ezd6ez8ff4e6/pulls/comments/juyghb6g8c4vfe1dfer57"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_149, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_149).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/user/repos");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_150, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_150).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "uhtrdfs6dc84sf";
        });

        router->call("GET", "/users/uhtrdfs6dc84sf/repos");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_151, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_151).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "zrf68c4zf1z6d84";
        });

        router->call("GET", "/orgs/zrf68c4zf1z6d84/repos");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_152, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_152).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/repositories");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_153, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_153).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("POST", "/user/repos");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_154, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_154).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("org")->second == "yger65f41refr";
        });

        router->call("POST", "/orgs/yger65f41refr/repos");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_155, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_155).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "htrdg6vt8ed4gvd6fxgre"
                && ctx.params.find("repo")->second == "rerf6ez8d41ezf6s8ezr";
        });

        router->call("GET", "/repos/htrdg6vt8ed4gvd6fxgre/rerf6ez8d41ezf6s8ezr");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_156, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_156).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "resgtf6cd8s4fe"
                && ctx.params.find("repo")->second == "96re54stf6rz8rf4ez";
        });

        router->call("PATCH", "/repos/resgtf6cd8s4fe/96re54stf6rz8rf4ez");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_157, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_157).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "refklskdjzmedlsdc5c16"
                && ctx.params.find("repo")->second == "654gedf6src54f6c5sdf4";
        });

        router->call("GET", "/repos/refklskdjzmedlsdc5c16/654gedf6src54f6c5sdf4/contributors");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_158, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_158).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "6r54ef6fe4ceer4fee"
                && ctx.params.find("repo")->second == "vces1dwf8crs4f3erz5d4";
        });

        router->call("GET", "/repos/6r54ef6fe4ceer4fee/vces1dwf8crs4f3erz5d4/languages");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_159, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_159).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "5r4e3fs5d4ez6d5ez43d5ez4"
                && ctx.params.find("repo")->second == "65e4gf6csrf4ce3sf5re4";
        });

        router->call("GET", "/repos/5r4e3fs5d4ez6d5ez43d5ez4/65e4gf6csrf4ce3sf5re4/teams");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_160, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_160).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "5s4f6z5sd1x6d5c4zde651"
                && ctx.params.find("repo")->second == "bvrezfd5erfrg5fezf9re";
        });

        router->call("GET", "/repos/5s4f6z5sd1x6d5c4zde651/bvrezfd5erfrg5fezf9re/tags");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_161, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_161).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "d65r4gf6ef84ez6dez4d6z"
                && ctx.params.find("repo")->second == "c1re6f8e4zsd6ez8d4ezd";
        });

        router->call("GET", "/repos/d65r4gf6ef84ez6dez4d6z/c1re6f8e4zsd6ez8d4ezd/branches");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_162, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_162).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "6e5f4d6zq8d46zed4ez6"
                && ctx.params.find("repo")->second == "bythrtgfse6dx4dz"
                && ctx.params.find("branch")->second == "tgfzeq6d8re4gers6";
        });

        router->call("GET", "/repos/6e5f4d6zq8d46zed4ez6/bythrtgfse6dx4dz/branches/tgfzeq6d8re4gers6");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_163, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_163).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ret6f4dz1sef68er"
                && ctx.params.find("repo")->second == "hger4f6erf4ed";
        });

        router->call("DELETE", "/repos/ret6f4dz1sef68er/hger4f6erf4ed");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_164, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_164).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "z56fe1d3z5d1z6ed4ze"
                && ctx.params.find("repo")->second == "e35f4dze3d5e1z3d5";
        });

        router->call("GET", "/repos/z56fe1d3z5d1z6ed4ze/e35f4dze3d5e1z3d5/collaborators");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_165, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_165).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "6s5f4d16xezd41zd6ze5d1z"
                && ctx.params.find("repo")->second == "z6fe5d4ze6dez4d6z54"
                && ctx.params.find("user")->second == "ger6s5f4dzex5zd6fe4d";
        });

        router->call(
            "GET",
            "/repos/6s5f4d16xezd41zd6ze5d1z/z6fe5d4ze6dez4d6z54/collaborators/ger6s5f4dzex5zd6fe4d"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_166, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_166).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "r6g5f41e3c5e1f6dz5edez"
                && ctx.params.find("repo")->second == "gf6dsdxezf5de1cs6xez"
                && ctx.params.find("user")->second == "iojh4fgdxv3c54e1fc3d";
        });

        router->call(
            "PUT",
            "/repos/r6g5f41e3c5e1f6dz5edez/gf6dsdxezf5de1cs6xez/collaborators/iojh4fgdxv3c54e1fc3d"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_167, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_167).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "jhtr6ef5d1zdefd6ezdez6"
                && ctx.params.find("repo")->second == "vcz6ed4xzsc6xz5cx4sd6x"
                && ctx.params.find("user")->second == "aed6xz5c4x1dz6x5zw16zd8";
        });

        router->call(
            "DELETE",
            "/repos/jhtr6ef5d1zdefd6ezdez6/vcz6ed4xzsc6xz5cx4sd6x/collaborators/aed6xz5c4x1dz6x5zw16zd8"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_168, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_168).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "iuh6grtss5c41ref65e4zds61"
                && ctx.params.find("repo")->second == "yrhgf6red51x6cz54e6";
        });

        router->call("GET", "/repos/iuh6grtss5c41ref65e4zds61/yrhgf6red51x6cz54e6/comments");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_169, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_169).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "hregfdze1d6zee5"
                && ctx.params.find("repo")->second == "jytrefdsq6x54rezf"
                && ctx.params.find("sha")->second == "kjthrgfcxd6ffrzd5";
        });

        router->call("GET", "/repos/hregfdze1d6zee5/jytrefdsq6x54rezf/commits/kjthrgfcxd6ffrzd5/comments");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_170, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_170).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "gefd65xe4zd6zed54"
                && ctx.params.find("repo")->second == "href65rz4d6dzd4ze"
                && ctx.params.find("sha")->second == "rf6sde4f6ef4d6ze5fd4ez";
        });

        router->call(
            "POST",
            "/repos/gefd65xe4zd6zed54/href65rz4d6dzd4ze/commits/rf6sde4f6ef4d6ze5fd4ez/comments"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_171, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_171).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "tgezf65de4z6d5ez4d6ez6dz4dz"
                && ctx.params.find("repo")->second == "gre35f4re6f5e1zd6ezfz6"
                && ctx.params.find("id")->second == "e65grf4d6ezd54ze6d54z6d5";
        });

        router->call(
            "GET",
            "/repos/tgezf65de4z6d5ez4d6ez6dz4dz/gre35f4re6f5e1zd6ezfz6/comments/e65grf4d6ezd54ze6d54z6d5"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_172, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_172).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "hgerz6d55e4zf6re5z4d"
                && ctx.params.find("repo")->second == "gre6f51d6ez5d4ze6d5z1"
                && ctx.params.find("id")->second == "hrtgefs5cd1ez3f5fe";
        });

        router->call(
            "PATCH",
            "/repos/hgerz6d55e4zf6re5z4d/gre6f51d6ez5d4ze6d5z1/comments/hrtgefs5cd1ez3f5fe"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_173, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_173).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "g3r5f1fe56rfger6f5re"
                && ctx.params.find("repo")->second == "ythr6gdrf5dc41xz"
                && ctx.params.find("id")->second == "j-y(regf3c54fr6ef54e";
        });

        router->call("DELETE", "/repos/g3r5f1fe56rfger6f5re/ythr6gdrf5dc41xz/comments/j-y(regf3c54fr6ef54e");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_174, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_174).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ythyrgerfc65erzf"
                && ctx.params.find("repo")->second == "rtge6fs5ed4+6fer4c";
        });

        router->call("GET", "/repos/ythyrgerfc65erzf/rtge6fs5ed4+6fer4c/commits");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_175, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_175).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "thgr6e5zd4ezfre4fz5"
                && ctx.params.find("repo")->second == "-(hrgefzed654zd65"
                && ctx.params.find("sha")->second == "èytfyhxtgfcdz6cez";
        });

        router->call("GET", "/repos/thgr6e5zd4ezfre4fz5/-(hrgefzed654zd65/commits/èytfyhxtgfcdz6cez");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_176, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_176).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "yrhgdfsd65xefrs65"
                && ctx.params.find("repo")->second == "ythrgrf3654ergf6s5d4";
        });

        router->call("GET", "/repos/yrhgdfsd65xefrs65/ythrgrf3654ergf6s5d4/readme");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_177, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_177).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "jtrdf65e4f6sf5s4"
                && ctx.params.find("repo")->second == "jhres6fed5ezf6dez"
                && ctx.remaining_path == "tyrhdg6fs5d4der6f5c4dg65dg4dr6f5ge6fs5c1sf5c46sf5e4c6ds56zesf54zetrgd6r8f4er6z84dez684d";
        });

        router->call(
            "GET",
            "/repos/jtrdf65e4f6sf5s4/jhres6fed5ezf6dez/contents/"
            "tyrhdg6fs5d4der6f5c4dg65dg4dr6f5ge6fs5c1sf5c46sf5e4c6ds56zesf54zetrgd6r8f4er6z84dez684d"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_178, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_178).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "j(hregr6fe54d6ez84"
                && ctx.params.find("repo")->second == "tyjrth6drxf4cez6r5ze4"
                && ctx.remaining_path == "jhtr6erf4r6f846re8g4fezq6d846reg4ves6fd8ze4f1ez6r8d4ezqdé6";
        });

        router->call(
            "PUT",
            "/repos/j(hregr6fe54d6ez84/tyjrth6drxf4cez6r5ze4/contents/"
            "jhtr6erf4r6f846re8g4fezq6d846reg4ves6fd8ze4f1ez6r8d4ezqdé6"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_179, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_179).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ètjh6gdc4dz654ez"
                && ctx.params.find("repo")->second == "rd-h5gf4zq6edez46d4"
                && ctx.remaining_path == "truy6dgr8fcd4ez6sf84rez6sf8d4ezsfdc6zes8f4czes6";
        });

        router->call(
            "DELETE",
            "/repos/ètjh6gdc4dz654ez/rd-h5gf4zq6edez46d4/contents/"
            "truy6dgr8fcd4ez6sf84rez6sf8d4ezsfdc6zes8f4czes6"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_180, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_180).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "rgefr6c4ref6re5fz"
                && ctx.params.find("repo")->second == "gerzd65x4z6ed84xz6d84"
                && ctx.params.find("id")->second == "tergfsd5e1ezs5d4z";
        });

        router->call("GET", "/repos/rgefr6c4ref6re5fz/gerzd65x4z6ed84xz6d84/keys/tergfsd5e1ezs5d4z");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_181, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_181).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "e4gf6ef41ez6dez541d0"
                && ctx.params.find("repo")->second == "oikujh4gvcds6"
                && ctx.params.find("id")->second == "th4fgdv6sf3d54f1ec0dxe5dfx2c";
        });

        router->call(
            "GET",
            "/repos/e4gf6ef41ez6dez541d0/oikujh4gvcds6/downloads/th4fgdv6sf3d54f1ec0dxe5dfx2c"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_182, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_182).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "6v8tr4ec6r8gf4ref16ref54"
                && ctx.params.find("repo")->second == "6r5etg4fc1r6dvc4r1d6r84"
                && ctx.params.find("id")->second == "3fe5s4cfed638v4cfd";
        });

        router->call(
            "GET",
            "/repos/6v8tr4ec6r8gf4ref16ref54/6r5etg4fc1r6dvc4r1d6r84/hooks/3fe5s4cfed638v4cfd"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_183, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_183).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "nhgtersd6xesf"
                && ctx.params.find("repo")->second == "ytrescc4dfscre6"
                && ctx.params.find("id")->second == "xcgre6f54c1ezsdxe2r4f";
        });

        router->call("GET", "/repos/nhgtersd6xesf/ytrescc4dfscre6/releases/xcgre6f54c1ezsdxe2r4f");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_184, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_184).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "jhtyh35y1ht3y53ht1"
                && ctx.params.find("repo")->second == "65r1f2cz0sed65zed";
        });

        router->call("GET", "/repos/jhtyh35y1ht3y53ht1/65r1f2cz0sed65zed/stats/contributors");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_185, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_185).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "633czd6ze2xccez6dz"
                && ctx.params.find("repo")->second == "716cz5c1zsc6310cz";
        });

        router->call("GET", "/repos/633czd6ze2xccez6dz/716cz5c1zsc6310cz/stats/commit_activity");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_186, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_186).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "p6zd6z5edz6x50z"
                && ctx.params.find("repo")->second == "w61e0dxe6dx1s365ze1d";
        });

        router->call("GET", "/repos/p6zd6z5edz6x50z/w61e0dxe6dx1s365ze1d/stats/code_frequency");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_187, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_187).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "cg6e5g1ce6fece65c1dc51"
                && ctx.params.find("repo")->second == "q6ljj62hjn62ghbgf61f";
        });

        router->call("GET", "/repos/cg6e5g1ce6fece65c1dc51/q6ljj62hjn62ghbgf61f/stats/participation");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_188, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_188).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "c16ef51ce0c516c5sc1d"
                && ctx.params.find("repo")->second == "lkuy3jh5vtr10dgvr5d";
        });

        router->call("GET", "/repos/c16ef51ce0c516c5sc1d/lkuy3jh5vtr10dgvr5d/stats/punch_card");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_189, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_189).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "05gv2ce0r6fce2f0"
                && ctx.params.find("repo")->second == "vg5t1gv0fdr6f1zs3";
        });

        router->call("GET", "/repos/05gv2ce0r6fce2f0/vg5t1gv0fdr6f1zs3/statuses/{ref}");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_190, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_190).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "kzfz21dzx0zed21ez63d51ez"
                && ctx.params.find("repo")->second == "qd1x0dsc6zs2cze1dz0sc56ds1c";
        });

        router->call("POST", "/repos/kzfz21dzx0zed21ez63d51ez/qd1x0dsc6zs2cze1dz0sc56ds1c/statuses/{ref}");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_191, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_191).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "yregt68sf4cze6d84ze6dze8d4q"
                && ctx.params.find("repo")->second == "trg6efs5red1c6ez5fsd4zesf5dez"
                && ctx.params.find("archive_format")->second == "trhdgfr6ef54ze6dze4dze6d8ze41sdez65d"
                && ctx.params.find("ref")->second == "'refzde65zf4d1exzes6eqd5ze4'";
        });

        router->call(
            "GET",
            "/repos/yregt68sf4cze6d84ze6dze8d4q/trg6efs5red1c6ez5fsd4zesf5dez/"
            "trhdgfr6ef54ze6dze4dze6d8ze41sdez65d/'refzde65zf4d1exzes6eqd5ze4'"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_192, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_192).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "tegsfed646xez+f6erfref+e65"
                && ctx.params.find("repo")->second == "rhd6grsfd4cez6dze4";
        });

        router->call("GET", "/repos/tegsfed646xez+f6erfref+e65/rhd6grsfd4cez6dze4/keys");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_193, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_193).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "gefs6dz4dez6d84z"
                && ctx.params.find("repo")->second == "ters6d4re6f8drz4d6e84";
        });

        router->call("POST", "/repos/gefs6dz4dez6d84z/ters6d4re6f8drz4d6e84/keys");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_194, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_194).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "hgerfsdgers6f5cze"
                && ctx.params.find("repo")->second == "tergcdzfdezkeys"
                && ctx.params.find("id")->second == "rergfsedsfzqdfedz";
        });

        router->call("PATCH", "/repos/hgerfsdgers6f5cze/tergcdzfdezkeys/keys/rergfsedsfzqdfedz");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_195, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_195).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "tre5gf46z5d4e6"
                && ctx.params.find("repo")->second == "0v5869esf1cz0"
                && ctx.params.find("id")->second == "drgfze6q8x4cre1sfcer5";
        });

        router->call("DELETE", "/repos/tre5gf46z5d4e6/0v5869esf1cz0/keys/drgfze6q8x4cre1sfcer5");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_196, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_196).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "gerfureflfezfres5fce1rf"
                && ctx.params.find("repo")->second == "5f1tdgve6drfc4e1";
        });

        router->call("GET", "/repos/gerfureflfezfres5fce1rf/5f1tdgve6drfc4e1/downloads");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_197, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_197).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "tgef6c54ef1ce86"
                && ctx.params.find("repo")->second == "tgefsdc5e4fsc1eswd5ced"
                && ctx.params.find("id")->second == "refcs5ed41ezds0cx5eds2efd1";
        });

        router->call(
            "DELETE",
            "/repos/tgef6c54ef1ce86/tgefsdc5e4fsc1eswd5ced/downloads/refcs5ed41ezds0cx5eds2efd1"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_198, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_198).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "trg4df6scd54c1eds0"
                && ctx.params.find("repo")->second == "te65rf4c1re0sdfcre5";
        });

        router->call("GET", "/repos/trg4df6scd54c1eds0/te65rf4c1re0sdfcre5/forks");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_199, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_199).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ef6s5df4efez46dze8"
                && ctx.params.find("repo")->second == "trstfd6cez5fe1dez";
        });

        router->call("POST", "/repos/ef6s5df4efez46dze8/trstfd6cez5fe1dez/forks");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_200, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_200).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "1rdfc9sd65f41ez"
                && ctx.params.find("repo")->second == "6r35zsf41refde6z85";
        });

        router->call("GET", "/repos/1rdfc9sd65f41ez/6r35zsf41refde6z85/hooks");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_201, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_201).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "rfz356c4e6zedez4"
                && ctx.params.find("repo")->second == "e6r5f4c1z6s8dc4ez";
        });

        router->call("POST", "/repos/rfz356c4e6zedez4/e6r5f4c1z6s8dc4ez/hooks");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_202, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_202).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "e6sr5f4c1ds6c8xz4"
                && ctx.params.find("repo")->second == "s6f5dc41dzsdxez56d"
                && ctx.params.find("id")->second == "zefd564xze6d8ez4dzx";
        });

        router->call("PATCH", "/repos/e6sr5f4c1ds6c8xz4/s6f5dc41dzsdxez56d/hooks/zefd564xze6d8ez4dzx");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_203, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_203).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "e6rf54dxz6d8ezd4zx"
                && ctx.params.find("repo")->second == "s6dc4dxzs6dxezsq54dz"
                && ctx.params.find("id")->second == "d65ez41dxez6d8ez4";
        });

        router->call("POST", "/repos/e6rf54dxz6d8ezd4zx/s6dc4dxzs6dxezsq54dz/hooks/d65ez41dxez6d8ez4/tests");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_204, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_204).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ze6d54z6d8z4ed"
                && ctx.params.find("repo")->second == "48c6z5d1x6z5d41xezd0x"
                && ctx.params.find("id")->second == "6edz1dx0ezdx5ezd1x";
        });

        router->call("DELETE", "/repos/ze6d54z6d8z4ed/48c6z5d1x6z5d41xezd0x/hooks/6edz1dx0ezdx5ezd1x");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_205, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_205).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "z6ef8d4x1z"
                && ctx.params.find("repo")->second == "brefs6d8x4dzs1";
        });

        router->call("POST", "/repos/z6ef8d4x1z/brefs6d8x4dzs1/merges");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_206, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_206).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "rez6f5sdxez2de6"
                && ctx.params.find("repo")->second == "wfgf4erdxwerf5d4";
        });

        router->call("GET", "/repos/rez6f5sdxez2de6/wfgf4erdxwerf5d4/releases");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_207, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_207).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ikujhgrf4cre6dgf4efer8f4"
                && ctx.params.find("repo")->second == "wcnyhgv1c6s8rf4zsd";
        });

        router->call("POST", "/repos/ikujhgrf4cre6dgf4efer8f4/wcnyhgv1c6s8rf4zsd/releases");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_208, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_208).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "zfczed65xze2dze"
                && ctx.params.find("repo")->second == "uyhtrgdfvcdsferf9f8c4d"
                && ctx.params.find("id")->second == "eezdxergerf4c6e4ceds4";
        });

        router->call("PATCH", "/repos/zfczed65xze2dze/uyhtrgdfvcdsferf9f8c4d/releases/eezdxergerf4c6e4ceds4");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_209, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_209).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "ef65c1dsc6ez52cd"
                && ctx.params.find("repo")->second == "mlkjghc6v2fd"
                && ctx.params.find("id")->second == "lcdzcbezidz51ce6cs";
        });

        router->call("DELETE", "/repos/ef65c1dsc6ez52cd/mlkjghc6v2fd/releases/lcdzcbezidz51ce6cs");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_210, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_210).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "edd62rfcs6fc200620"
                && ctx.params.find("repo")->second == "0256efv1c0efs5f2"
                && ctx.params.find("id")->second == "541srf0cr5esfc1es6c5ec1d0sc5";
        });

        router->call(
            "GET",
            "/repos/edd62rfcs6fc200620/0256efv1c0efs5f2/releases/541srf0cr5esfc1es6c5ec1d0sc5/assets"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_211, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_211).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/search/repositories");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_212, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_212).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/search/code");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_213, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_213).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/search/issues");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_214, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_214).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/search/users");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_215, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_215).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("owner")->second == "0c563dzed1xe0zdxz6d"
                && ctx.params.find("repository")->second == "03d1z0d6xzed51xzed0x5ez6d51ze"
                && ctx.params.find("state")->second == "0ez6dxez12d6xzxzd6xzed"
                && ctx.params.find("keyword")->second == "kjnu2hgf6bgv5t1rdf0v";
        });

        router->call(
            "GET",
            "/legacy/issues/search/0c563dzed1xe0zdxz6d/03d1z0d6xzed51xzed0x5ez6d51ze/0ez6dxez12d6xzxzd6xzed/"
            "kjnu2hgf6bgv5t1rdf0v"
        );
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_216, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_216).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("keyword")->second == "39ed41xz5zeed1z5";
        });

        router->call("GET", "/legacy/repos/search/39ed41xz5zeed1z5");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_217, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_217).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("keyword")->second == "8zef4dz6d51zedz65ed41";
        });

        router->call("GET", "/legacy/user/search/8zef4dz6d51zedz65ed41");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_218, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_218).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("email")->second == "z65czd65zd@z4ed68ze.com";
        });

        router->call("GET", "/legacy/user/email/z65czd65zd@z4ed68ze.com");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_219, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_219).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "zf46ed4ze6d4zed4zed6z4xez6d";
        });

        router->call("GET", "/users/zf46ed4ze6d4zed4zed6z4xez6d");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_220, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_220).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/user");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_221, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_221).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("PATCH", "/user");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_222, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_222).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/users");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_223, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_223).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/user/emails");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_224, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_224).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("POST", "/user/emails");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_225, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_225).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("DELETE", "/user/emails");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_226, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_226).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "ed5z9ed5ez2d95zed";
        });

        router->call("GET", "/users/ed5z9ed5ez2d95zed/followers");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_227, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_227).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/user/followers");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_228, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_228).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "yju6f54grd51ef6r5f1er";
        });

        router->call("GET", "/users/yju6f54grd51ef6r5f1er/following");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_229, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_229).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/user/following");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_230, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_230).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "utyfthg6fze51dz";
        });

        router->call("GET", "/user/following/utyfthg6fze51dz");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_231, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_231).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "ytrg6dv5rc1dfc0e65fe"
                && ctx.params.find("target_user")->second == "9e8t4fdc1ze6qd4ez";
        });

        router->call("GET", "/users/ytrg6dv5rc1dfc0e65fe/following/9e8t4fdc1ze6qd4ez");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_232, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_232).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "e6gf51cre6f8re4fe6s8f4";
        });

        router->call("PUT", "/user/following/e6gf51cre6f8re4fe6s8f4");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_233, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_233).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "rfe54fcez6f5d41ez6fe4z";
        });

        router->call("DELETE", "/user/following/rfe54fcez6f5d41ez6fe4z");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_234, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_234).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("user")->second == "e65rgf41r6zf4rez6f5ezs41de6zd";
        });

        router->call("GET", "/users/e65rgf41r6zf4rez6f5ezs41de6zd/keys");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_235, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_235).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/user/keys");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_236, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_236).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "r6f4cz6sd4ze6sd41z6dz";
        });

        router->call("GET", "/user/keys/r6f4cz6sd4ze6sd41z6dz");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_237, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_237).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("POST", "/user/keys");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_238, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_238).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "g46ref54z6sf8d4ezd96xe8sc41esd6w";
        });

        router->call("PATCH", "/user/keys/g46ref54z6sf8d4ezd96xe8sc41esd6w");
    }

    BOOST_DATA_TEST_CASE_F(Github_Fixture, route_239, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_239).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "r9g68f451re6sfer4fe6";
        });

        router->call("DELETE", "/user/keys/r9g68f451re6sfer4fe6");
    }

BOOST_AUTO_TEST_SUITE_END()