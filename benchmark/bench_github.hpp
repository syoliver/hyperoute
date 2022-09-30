#pragma once

#ifndef __BENCH__HYPEROUTE__GITHUB__H__
#define __BENCH__HYPEROUTE__GITHUB__H__

// https://github.com/julienschmidt/go-http-routing-benchmark/blob/master/gplus_test.go

static void github_hyperoute_empty(const hyperoute::route_context& ctx)
{
}

template<std::shared_ptr<hyperoute::backend::router_backend> BackendFactory()>
class Github_HyperouteBenchmark : public ::benchmark::Fixture
{
protected:
    std::optional<hyperoute::router> r;

    void SetUp(const ::benchmark::State& state) BENCHMARK_OVERRIDE
    {
        auto backend = BackendFactory();
        hyperoute::builder builder(backend);

        std::error_condition ec;

        // OAuth Authorizations
        builder.add_route("/authorizations"                                 , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/authorizations/{id}"                            , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/authorizations"                                 , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/authorizations/clients/{client_id}"             , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/authorizations/{id}"                            , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/authorizations/{id}"                            , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/applications/{client_id}/tokens/{access_token}" , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/applications/{client_id}/tokens"                , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/applications/{client_id}/tokens/{access_token}" , ec, &github_hyperoute_empty).methods({"DELETE"});

        // Activity
        builder.add_route("/events"                                 , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/events"            , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/networks/{owner}/{repo}/events"         , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/orgs/{org}/events"                      , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/users/{user}/received_events"           , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/users/{user}/received_events/public"    , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/users/{user}/events"                    , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/users/{user}/events/public"             , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/users/{user}/events/orgs/{org}"         , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/feeds"                                  , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/notifications"                          , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/notifications"     , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/notifications"                          , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/repos/{owner}/{repo}/notifications"     , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/notifications/threads/{id}"             , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/notifications/threads/{id}"             , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/notifications/threads/{id}/subscription", ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/notifications/threads/{id}/subscription", ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/notifications/threads/{id}/subscription", ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/stargazers"        , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/users/{user}/starred"                   , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/starred"                           , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/starred/{owner}/{repo}"            , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/starred/{owner}/{repo}"            , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/user/starred/{owner}/{repo}"            , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/subscribers"       , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/users/{user}/subscriptions"             , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/subscriptions"                     , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/subscription"      , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/subscription"      , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/repos/{owner}/{repo}/subscription"      , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/user/subscriptions/{owner}/{repo}"      , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/subscriptions/{owner}/{repo}"      , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/user/subscriptions/{owner}/{repo}"      , ec, &github_hyperoute_empty).methods({"DELETE"});

        // Gists
        builder.add_route("/users/{user}/gists"     , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/gists"                  , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/gists/public"           , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/gists/starred"          , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/gists/{id}"             , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/gists"                  , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/gists/{id}"             , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/gists/{id}/star"        , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/gists/{id}/star"        , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/gists/{id}/star"        , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/gists/{id}/forks"       , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/gists/{id}"             , ec, &github_hyperoute_empty).methods({"DELETE"});

        // Git Data
        builder.add_route("/repos/{owner}/{repo}/git/blobs/{sha}"   , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/git/blobs"         , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/git/commits/{sha}" , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/git/commits"       , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route_prefix("/repos/{owner}/{repo}/git/refs/"  , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/git/refs"          , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/git/refs"          , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route_prefix("/repos/{owner}/{repo}/git/refs/"  , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route_prefix("/repos/{owner}/{repo}/git/refs/"  , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/git/tags/{sha}"    , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/git/tags"          , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/git/trees/{sha}"   , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/git/trees"         , ec, &github_hyperoute_empty).methods({"POST"});

        // Issues
        builder.add_route("/issues"                                             , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/issues"                                        , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/orgs/{org}/issues"                                  , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues"                        , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/comments"               , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/comments/{id}"          , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/events"                 , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}"               , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues"                        , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}"               , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/assignees"                     , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/assignees/{assignee}"          , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/comments"      , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/comments"      , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/issues/comments/{id}"          , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/issues/comments/{id}"          , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/events"        , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/events/{id}"            , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/labels"                        , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/labels/{name}"                 , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/labels"                        , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/labels/{name}"                 , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/labels/{name}"                 , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/labels"        , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/labels"        , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/labels/{name}" , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/labels"        , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/repos/{owner}/{repo}/issues/{number}/labels"        , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/milestones/{number}/labels"    , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/milestones"                    , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/milestones/{number}"           , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/milestones"                    , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/milestones/{number}"           , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/milestones/{number}"           , ec, &github_hyperoute_empty).methods({"DELETE"});
    
        // Miscellaneous
        builder.add_route("/emojis"                     , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/gitignore/templates"        , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/gitignore/templates/{name}" , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/markdown"                   , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/markdown/raw"               , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/meta"                       , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/rate_limit"                 , ec, &github_hyperoute_empty).methods({"GET"});

        // Organizations
        builder.add_route("/users/{user}/orgs"                  , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/orgs"                          , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/orgs/{org}"                         , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/orgs/{org}"                         , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/orgs/{org}/members"                 , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/orgs/{org}/members/{user}"          , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/orgs/{org}/members/{user}"          , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/orgs/{org}/public_members"          , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/orgs/{org}/public_members/{user}"   , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/orgs/{org}/public_members/{user}"   , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/orgs/{org}/public_members/{user}"   , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/orgs/{org}/teams"                   , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/teams/{id}"                         , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/orgs/{org}/teams"                   , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/teams/{id}"                         , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/teams/{id}"                         , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/teams/{id}/members"                 , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/teams/{id}/members/{user}"          , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/teams/{id}/members/{user}"          , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/teams/{id}/members/{user}"          , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/teams/{id}/repos"                   , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/teams/{id}/repos/{owner}/{repo}"    , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/teams/{id}/repos/{owner}/{repo}"    , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/teams/{id}/repos/{owner}/{repo}"    , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/user/teams"                         , ec, &github_hyperoute_empty).methods({"GET"});


        // Pull Requests
        builder.add_route("/repos/{owner}/{repo}/pulls"                     , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/comments"            , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}"            , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls"                     , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}"            , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}/commits"    , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}/files"      , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}/merge"      , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}/merge"      , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}/comments"   , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/comments/{number}"   , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/pulls/{number}/comments"   , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/repos/{owner}/{repo}/pulls/comments/{number}"   , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/pulls/comments/{number}"   , ec, &github_hyperoute_empty).methods({"DELETE"});

        // Repositories
        builder.add_route("/user/repos"                                 , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/users/{user}/repos"                         , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/orgs/{org}/repos"                           , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repositories"                               , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/repos"                                 , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/orgs/{org}/repos"                           , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}"                       , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}"                       , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/contributors"          , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/languages"             , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/teams"                 , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/tags"                  , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/branches"              , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/branches/{branch}"     , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}"                       , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/collaborators"         , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/collaborators/{user}"  , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/collaborators/{user}"  , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/repos/{owner}/{repo}/collaborators/{user}"  , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/comments"              , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/commits/{sha}/comments", ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/commits/{sha}/comments", ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/comments/{id}"         , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/comments/{id}"         , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/comments/{id}"         , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/commits"               , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/commits/{sha}"         , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/readme"                , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route_prefix("/repos/{owner}/{repo}/contents/"      , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route_prefix("/repos/{owner}/{repo}/contents/"      , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route_prefix("/repos/{owner}/{repo}/contents/"      , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/keys/{id}"             , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/downloads/{id}"        , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/hooks/{id}"            , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/releases/{id}"         , ec, &github_hyperoute_empty).methods({"GET"});

        builder.add_route("/repos/{owner}/{repo}/stats/contributors"    , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/stats/commit_activity" , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/stats/code_frequency"  , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/stats/participation"   , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/stats/punch_card"      , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/statuses/{ref}"        , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/statuses/{ref}"        , ec, &github_hyperoute_empty).methods({"POST"});

        builder.add_route("/repos/{owner}/{repo}/{archive_format}/{ref}", ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/keys"                  , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/keys"                  , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/keys/{id}"             , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/keys/{id}"             , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/downloads"             , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/downloads/{id}"        , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/forks"                 , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/forks"                 , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/hooks"                 , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/hooks"                 , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/hooks/{id}"            , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/hooks/{id}/tests"      , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/hooks/{id}"            , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/merges"                , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/releases"              , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/repos/{owner}/{repo}/releases"              , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/repos/{owner}/{repo}/releases/{id}"         , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/repos/{owner}/{repo}/releases/{id}"         , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/repos/{owner}/{repo}/releases/{id}/assets"  , ec, &github_hyperoute_empty).methods({"GET"});


        // Search
        builder.add_route("/search/repositories"                                        , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/search/code"                                                , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/search/issues"                                              , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/search/users"                                               , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/legacy/issues/search/{owner}/{repository}/{state}/{keyword}", ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/legacy/repos/search/{keyword}"                              , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/legacy/user/search/{keyword}"                               , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/legacy/user/email/{email}"                                  , ec, &github_hyperoute_empty).methods({"GET"});


        // Users
        builder.add_route("/users/{user}"                           , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user"                                   , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user"                                   , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/users"                                  , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/emails"                            , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/emails"                            , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/user/emails"                            , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/users/{user}/followers"                 , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/followers"                         , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/users/{user}/following"                 , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/following"                         , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/following/{user}"                  , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/users/{user}/following/{target_user}"   , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/following/{user}"                  , ec, &github_hyperoute_empty).methods({"PUT"});
        builder.add_route("/user/following/{user}"                  , ec, &github_hyperoute_empty).methods({"DELETE"});
        builder.add_route("/users/{user}/keys"                      , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/keys"                              , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/keys/{id}"                         , ec, &github_hyperoute_empty).methods({"GET"});
        builder.add_route("/user/keys"                              , ec, &github_hyperoute_empty).methods({"POST"});
        builder.add_route("/user/keys/{id}"                         , ec, &github_hyperoute_empty).methods({"PATCH"});
        builder.add_route("/user/keys/{id}"                         , ec, &github_hyperoute_empty).methods({"DELETE"});

        r = builder.build(ec);
    }

    void TearDown(const ::benchmark::State& state) BENCHMARK_OVERRIDE
    {
        r = std::nullopt;
    }

    void Execute(::benchmark::State& state)
    {

        CALLGRIND_START_INSTRUMENTATION;
        for (auto _ : state)
        {
            Execute();
        }
        CALLGRIND_STOP_INSTRUMENTATION;
    }

    void Execute()
    {
        CALLGRIND_TOGGLE_COLLECT;
        r->call("GET", "/user/keys");
        r->call("POST", "/user/keys");
        r->call("PUT", "/user/following/486546843546546546");
        r->call("GET", "/legacy/issues/search/565435413654651651/65435146516351654/54684351351/1568463516");
        r->call("GET", "/repos/65435143513514/6543513543513/releases/165435135416541");
        r->call("GET", "/repos/6543543541354654/6543531546565/contents/a/big/content");
        r->call("GET", "/repositories");
        r->call("DELETE", "/repos/15654354654654/165435135416543/pulls/comments/1654351435413513");
        r->call("GET", "/teams/65465454654654/repos/4654354354654/465413516541321");
        r->call("PUT", "/teams/65465454654654/repos/56465465146/456543513546546641541");


        r->call("GET", "/users/146545136561645451/orgs");
        r->call("GET", "/gists");
        r->call("GET", "/markdown");
        r->call("GET", "/repos/163545435435/46543516546545/issues/comments/156543546546514");
        r->call("GET", "/repos/1654351351543/135435135135/issues/354365413513514/comments");
        r->call("DELETE", "/authorizations/1354654151545");
        r->call("GET", "/applications/841165616164161616/tokens/1654654516565");
        r->call("GET", "/user/keys");
        r->call("GET", "/legacy/user/email/15654564");
        r->call("GET", "/not/found");

        CALLGRIND_TOGGLE_COLLECT;
    }
};


BENCHMARK_TEMPLATE_F(Github_HyperouteBenchmark, Hyperouter_Simple, &hyperoute::backend::make_simple)(benchmark::State& st)
{
    Execute(st);
}

BENCHMARK_TEMPLATE_F(Github_HyperouteBenchmark, Hyperouter_Hyperscan, &hyperoute::backend::make_hyperscan)(benchmark::State& st)
{
    Execute(st);
}

BENCHMARK_TEMPLATE_F(Github_HyperouteBenchmark, Hyperouter_Boost, &hyperoute::backend::make_boost)(benchmark::State& st)
{
    Execute(st);
}

#ifdef WITH_R3

class Github_R3Benchmark : public ::benchmark::Fixture
{
protected:
    node *n = nullptr;

    std::vector<int> route_data;


    Github_R3Benchmark()
    {
        for(int i = 0 ; i < 300 ; ++i) route_data.push_back(i);
    }

    void SetUp(const ::benchmark::State& state) BENCHMARK_OVERRIDE
    {
        n = r3_tree_create(10);

        // OAuth Authorizations
        r3_tree_insert_routel(n, METHOD_GET,    "/authorizations"                                 , sizeof("/authorizations")                                  - 1, &route_data[0]);
        r3_tree_insert_routel(n, METHOD_GET,    "/authorizations/{id}"                            , sizeof("/authorizations/{id}")                             - 1, &route_data[1]);
        r3_tree_insert_routel(n, METHOD_POST,   "/authorizations"                                 , sizeof("/authorizations")                                  - 1, &route_data[2]);
        r3_tree_insert_routel(n, METHOD_PUT,    "/authorizations/clients/{client_id}"             , sizeof("/authorizations/clients/{client_id}")              - 1, &route_data[3]);
        r3_tree_insert_routel(n, METHOD_PATCH,  "/authorizations/{id}"                            , sizeof("/authorizations/{id}")                             - 1, &route_data[4]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/authorizations/{id}"                            , sizeof("/authorizations/{id}")                             - 1, &route_data[5]);
        r3_tree_insert_routel(n, METHOD_GET,    "/applications/{client_id}/tokens/{access_token}" , sizeof("/applications/{client_id}/tokens/{access_token}")  - 1, &route_data[6]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/applications/{client_id}/tokens"                , sizeof("/applications/{client_id}/tokens")                 - 1, &route_data[7]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/applications/{client_id}/tokens/{access_token}" , sizeof("/applications/{client_id}/tokens/{access_token}")  - 1, &route_data[8]);

        // Activity
        r3_tree_insert_routel(n, METHOD_GET,    "/events"                                 , sizeof("/events"                                 ) -1, &route_data[ 9]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/events"            , sizeof("/repos/{owner}/{repo}/events"            ) -1, &route_data[10]);
        r3_tree_insert_routel(n, METHOD_GET,    "/networks/{owner}/{repo}/events"         , sizeof("/networks/{owner}/{repo}/events"         ) -1, &route_data[11]);
        r3_tree_insert_routel(n, METHOD_GET,    "/orgs/{org}/events"                      , sizeof("/orgs/{org}/events"                      ) -1, &route_data[12]);
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}/received_events"           , sizeof("/users/{user}/received_events"           ) -1, &route_data[13]);
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}/received_events/public"    , sizeof("/users/{user}/received_events/public"    ) -1, &route_data[14]);
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}/events"                    , sizeof("/users/{user}/events"                    ) -1, &route_data[15]);
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}/events/public"             , sizeof("/users/{user}/events/public"             ) -1, &route_data[16]);
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}/events/orgs/{org}"         , sizeof("/users/{user}/events/orgs/{org}"         ) -1, &route_data[17]);
        r3_tree_insert_routel(n, METHOD_GET,    "/feeds"                                  , sizeof("/feeds"                                  ) -1, &route_data[18]);
        r3_tree_insert_routel(n, METHOD_GET,    "/notifications"                          , sizeof("/notifications"                          ) -1, &route_data[19]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/notifications"     , sizeof("/repos/{owner}/{repo}/notifications"     ) -1, &route_data[20]);
        r3_tree_insert_routel(n, METHOD_PUT,    "/notifications"                          , sizeof("/notifications"                          ) -1, &route_data[21]);
        r3_tree_insert_routel(n, METHOD_PUT,    "/repos/{owner}/{repo}/notifications"     , sizeof("/repos/{owner}/{repo}/notifications"     ) -1, &route_data[22]);
        r3_tree_insert_routel(n, METHOD_GET,    "/notifications/threads/{id}"             , sizeof("/notifications/threads/{id}"             ) -1, &route_data[23]);
        r3_tree_insert_routel(n, METHOD_PATCH,  "/notifications/threads/{id}"             , sizeof("/notifications/threads/{id}"             ) -1, &route_data[24]);
        r3_tree_insert_routel(n, METHOD_GET,    "/notifications/threads/{id}/subscription", sizeof("/notifications/threads/{id}/subscription") -1, &route_data[25]);
        r3_tree_insert_routel(n, METHOD_PUT,    "/notifications/threads/{id}/subscription", sizeof("/notifications/threads/{id}/subscription") -1, &route_data[26]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/notifications/threads/{id}/subscription", sizeof("/notifications/threads/{id}/subscription") -1, &route_data[27]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/stargazers"        , sizeof("/repos/{owner}/{repo}/stargazers"        ) -1, &route_data[28]);
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}/starred"                   , sizeof("/users/{user}/starred"                   ) -1, &route_data[29]);
        r3_tree_insert_routel(n, METHOD_GET,    "/user/starred"                           , sizeof("/user/starred"                           ) -1, &route_data[30]);
        r3_tree_insert_routel(n, METHOD_GET,    "/user/starred/{owner}/{repo}"            , sizeof("/user/starred/{owner}/{repo}"            ) -1, &route_data[31]);
        r3_tree_insert_routel(n, METHOD_PUT,    "/user/starred/{owner}/{repo}"            , sizeof("/user/starred/{owner}/{repo}"            ) -1, &route_data[32]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/user/starred/{owner}/{repo}"            , sizeof("/user/starred/{owner}/{repo}"            ) -1, &route_data[33]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/subscribers"       , sizeof("/repos/{owner}/{repo}/subscribers"       ) -1, &route_data[34]);
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}/subscriptions"             , sizeof("/users/{user}/subscriptions"             ) -1, &route_data[35]);
        r3_tree_insert_routel(n, METHOD_GET,    "/user/subscriptions"                     , sizeof("/user/subscriptions"                     ) -1, &route_data[36]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/subscription"      , sizeof("/repos/{owner}/{repo}/subscription"      ) -1, &route_data[37]);
        r3_tree_insert_routel(n, METHOD_PUT,    "/repos/{owner}/{repo}/subscription"      , sizeof("/repos/{owner}/{repo}/subscription"      ) -1, &route_data[38]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/repos/{owner}/{repo}/subscription"      , sizeof("/repos/{owner}/{repo}/subscription"      ) -1, &route_data[39]);
        r3_tree_insert_routel(n, METHOD_GET,    "/user/subscriptions/{owner}/{repo}"      , sizeof("/user/subscriptions/{owner}/{repo}"      ) -1, &route_data[40]);
        r3_tree_insert_routel(n, METHOD_PUT,    "/user/subscriptions/{owner}/{repo}"      , sizeof("/user/subscriptions/{owner}/{repo}"      ) -1, &route_data[41]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/user/subscriptions/{owner}/{repo}"      , sizeof("/user/subscriptions/{owner}/{repo}"      ) -1, &route_data[42]);


        // Gists
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}/gists"     , sizeof("/users/{user}/gists"     ) - 1, &route_data[43]);
        r3_tree_insert_routel(n, METHOD_GET,    "/gists"                  , sizeof("/gists"                  ) - 1, &route_data[44]);
        r3_tree_insert_routel(n, METHOD_GET,    "/gists/public"           , sizeof("/gists/public"           ) - 1, &route_data[45]);
        r3_tree_insert_routel(n, METHOD_GET,    "/gists/starred"          , sizeof("/gists/starred"          ) - 1, &route_data[46]);
        r3_tree_insert_routel(n, METHOD_GET,    "/gists/{id}"             , sizeof("/gists/{id}"             ) - 1, &route_data[47]);
        r3_tree_insert_routel(n, METHOD_POST,   "/gists"                  , sizeof("/gists"                  ) - 1, &route_data[48]);
        r3_tree_insert_routel(n, METHOD_PATCH,  "/gists/{id}"             , sizeof("/gists/{id}"             ) - 1, &route_data[49]);
        r3_tree_insert_routel(n, METHOD_PUT,    "/gists/{id}/star"        , sizeof("/gists/{id}/star"        ) - 1, &route_data[50]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/gists/{id}/star"        , sizeof("/gists/{id}/star"        ) - 1, &route_data[51]);
        r3_tree_insert_routel(n, METHOD_GET,    "/gists/{id}/star"        , sizeof("/gists/{id}/star"        ) - 1, &route_data[52]);
        r3_tree_insert_routel(n, METHOD_POST,   "/gists/{id}/forks"       , sizeof("/gists/{id}/forks"       ) - 1, &route_data[53]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/gists/{id}"             , sizeof("/gists/{id}"             ) - 1, &route_data[54]);

        // Git Data
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/git/blobs/{sha}"     , sizeof("/repos/{owner}/{repo}/git/blobs/{sha}"     ) - 1, &route_data[55]);
        r3_tree_insert_routel(n, METHOD_POST,   "/repos/{owner}/{repo}/git/blobs"           , sizeof("/repos/{owner}/{repo}/git/blobs"           ) - 1, &route_data[56]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/git/commits/{sha}"   , sizeof("/repos/{owner}/{repo}/git/commits/{sha}"   ) - 1, &route_data[57]);
        r3_tree_insert_routel(n, METHOD_POST,   "/repos/{owner}/{repo}/git/commits"         , sizeof("/repos/{owner}/{repo}/git/commits"         ) - 1, &route_data[58]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/git/refs/"           , sizeof("/repos/{owner}/{repo}/git/refs/"           ) - 1, &route_data[59]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/git/refs"            , sizeof("/repos/{owner}/{repo}/git/refs"            ) - 1, &route_data[60]);
        r3_tree_insert_routel(n, METHOD_POST,   "/repos/{owner}/{repo}/git/refs"            , sizeof("/repos/{owner}/{repo}/git/refs"            ) - 1, &route_data[61]);
        r3_tree_insert_routel(n, METHOD_PATCH,  "/repos/{owner}/{repo}/git/refs/"           , sizeof("/repos/{owner}/{repo}/git/refs/"           ) - 1, &route_data[62]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/repos/{owner}/{repo}/git/refs/"           , sizeof("/repos/{owner}/{repo}/git/refs/"           ) - 1, &route_data[63]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/git/tags/{sha}"      , sizeof("/repos/{owner}/{repo}/git/tags/{sha}"      ) - 1, &route_data[64]);
        r3_tree_insert_routel(n, METHOD_POST,   "/repos/{owner}/{repo}/git/tags"            , sizeof("/repos/{owner}/{repo}/git/tags"            ) - 1, &route_data[65]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/git/trees/{sha}"     , sizeof("/repos/{owner}/{repo}/git/trees/{sha}"     ) - 1, &route_data[66]);
        r3_tree_insert_routel(n, METHOD_POST,   "/repos/{owner}/{repo}/git/trees"           , sizeof("/repos/{owner}/{repo}/git/trees"           ) - 1, &route_data[67]);


        // Issues
        r3_tree_insert_routel(n, METHOD_GET,    "/issues"                                             , sizeof("/issues"                                             ) - 1, &route_data[68]);
        r3_tree_insert_routel(n, METHOD_GET,    "/user/issues"                                        , sizeof("/user/issues"                                        ) - 1, &route_data[69]);
        r3_tree_insert_routel(n, METHOD_GET,    "/orgs/{org}/issues"                                  , sizeof("/orgs/{org}/issues"                                  ) - 1, &route_data[70]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/issues"                        , sizeof("/repos/{owner}/{repo}/issues"                        ) - 1, &route_data[71]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/issues/{number}"               , sizeof("/repos/{owner}/{repo}/issues/{number}"               ) - 1, &route_data[72]);
        r3_tree_insert_routel(n, METHOD_POST,   "/repos/{owner}/{repo}/issues"                        , sizeof("/repos/{owner}/{repo}/issues"                        ) - 1, &route_data[73]);
        r3_tree_insert_routel(n, METHOD_PATCH,  "/repos/{owner}/{repo}/issues/{number}"               , sizeof("/repos/{owner}/{repo}/issues/{number}"               ) - 1, &route_data[74]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/assignees"                     , sizeof("/repos/{owner}/{repo}/assignees"                     ) - 1, &route_data[75]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/assignees/{assignee}"          , sizeof("/repos/{owner}/{repo}/assignees/{assignee}"          ) - 1, &route_data[76]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/issues/{number}/comments"      , sizeof("/repos/{owner}/{repo}/issues/{number}/comments"      ) - 1, &route_data[77]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/issues/comments"               , sizeof("/repos/{owner}/{repo}/issues/comments"               ) - 1, &route_data[78]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/issues/comments/{id}"          , sizeof("/repos/{owner}/{repo}/issues/comments/{id}"          ) - 1, &route_data[79]);
        r3_tree_insert_routel(n, METHOD_POST,   "/repos/{owner}/{repo}/issues/{number}/comments"      , sizeof("/repos/{owner}/{repo}/issues/{number}/comments"      ) - 1, &route_data[80]);
        r3_tree_insert_routel(n, METHOD_PATCH,  "/repos/{owner}/{repo}/issues/comments/{id}"          , sizeof("/repos/{owner}/{repo}/issues/comments/{id}"          ) - 1, &route_data[81]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/repos/{owner}/{repo}/issues/comments/{id}"          , sizeof("/repos/{owner}/{repo}/issues/comments/{id}"          ) - 1, &route_data[82]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/issues/{number}/events"        , sizeof("/repos/{owner}/{repo}/issues/{number}/events"        ) - 1, &route_data[83]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/issues/events"                 , sizeof("/repos/{owner}/{repo}/issues/events"                 ) - 1, &route_data[84]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/issues/events/{id}"            , sizeof("/repos/{owner}/{repo}/issues/events/{id}"            ) - 1, &route_data[85]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/labels"                        , sizeof("/repos/{owner}/{repo}/labels"                        ) - 1, &route_data[86]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/labels/{name}"                 , sizeof("/repos/{owner}/{repo}/labels/{name}"                 ) - 1, &route_data[87]);
        r3_tree_insert_routel(n, METHOD_POST,   "/repos/{owner}/{repo}/labels"                        , sizeof("/repos/{owner}/{repo}/labels"                        ) - 1, &route_data[88]);
        r3_tree_insert_routel(n, METHOD_PATCH,  "/repos/{owner}/{repo}/labels/{name}"                 , sizeof("/repos/{owner}/{repo}/labels/{name}"                 ) - 1, &route_data[89]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/repos/{owner}/{repo}/labels/{name}"                 , sizeof("/repos/{owner}/{repo}/labels/{name}"                 ) - 1, &route_data[90]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/issues/{number}/labels"        , sizeof("/repos/{owner}/{repo}/issues/{number}/labels"        ) - 1, &route_data[91]);
        r3_tree_insert_routel(n, METHOD_POST,   "/repos/{owner}/{repo}/issues/{number}/labels"        , sizeof("/repos/{owner}/{repo}/issues/{number}/labels"        ) - 1, &route_data[92]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/repos/{owner}/{repo}/issues/{number}/labels/{name}" , sizeof("/repos/{owner}/{repo}/issues/{number}/labels/{name}" ) - 1, &route_data[93]);
        r3_tree_insert_routel(n, METHOD_PUT,    "/repos/{owner}/{repo}/issues/{number}/labels"        , sizeof("/repos/{owner}/{repo}/issues/{number}/labels"        ) - 1, &route_data[94]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/repos/{owner}/{repo}/issues/{number}/labels"        , sizeof("/repos/{owner}/{repo}/issues/{number}/labels"        ) - 1, &route_data[95]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/milestones/{number}/labels"    , sizeof("/repos/{owner}/{repo}/milestones/{number}/labels"    ) - 1, &route_data[96]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/milestones"                    , sizeof("/repos/{owner}/{repo}/milestones"                    ) - 1, &route_data[97]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/milestones/{number}"           , sizeof("/repos/{owner}/{repo}/milestones/{number}"           ) - 1, &route_data[98]);
        r3_tree_insert_routel(n, METHOD_POST,   "/repos/{owner}/{repo}/milestones"                    , sizeof("/repos/{owner}/{repo}/milestones"                    ) - 1, &route_data[99]);
        r3_tree_insert_routel(n, METHOD_PATCH,  "/repos/{owner}/{repo}/milestones/{number}"           , sizeof("/repos/{owner}/{repo}/milestones/{number}"           ) - 1, &route_data[100]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/repos/{owner}/{repo}/milestones/{number}"           , sizeof("/repos/{owner}/{repo}/milestones/{number}"           ) - 1, &route_data[101]);
    
        // Miscellaneous
        r3_tree_insert_routel(n, METHOD_GET,    "/emojis"                     , sizeof("/emojis"                     ) - 1, &route_data[102]);
        r3_tree_insert_routel(n, METHOD_GET,    "/gitignore/templates"        , sizeof("/gitignore/templates"        ) - 1, &route_data[103]);
        r3_tree_insert_routel(n, METHOD_GET,    "/gitignore/templates/{name}" , sizeof("/gitignore/templates/{name}" ) - 1, &route_data[104]);
        r3_tree_insert_routel(n, METHOD_POST,   "/markdown"                   , sizeof("/markdown"                   ) - 1, &route_data[105]);
        r3_tree_insert_routel(n, METHOD_POST,   "/markdown/raw"               , sizeof("/markdown/raw"               ) - 1, &route_data[106]);
        r3_tree_insert_routel(n, METHOD_GET,    "/meta"                       , sizeof("/meta"                       ) - 1, &route_data[107]);
        r3_tree_insert_routel(n, METHOD_GET,    "/rate_limit"                 , sizeof("/rate_limit"                 ) - 1, &route_data[108]);



        // Organizations
        r3_tree_insert_routel(n, METHOD_GET,     "/users/{user}/orgs"                  , sizeof("/users/{user}/orgs"                  ) - 1, &route_data[109]);
        r3_tree_insert_routel(n, METHOD_GET,     "/user/orgs"                          , sizeof("/user/orgs"                          ) - 1, &route_data[110]);
        r3_tree_insert_routel(n, METHOD_GET,     "/orgs/{org}"                         , sizeof("/orgs/{org}"                         ) - 1, &route_data[111]);
        r3_tree_insert_routel(n, METHOD_PATCH,   "/orgs/{org}"                         , sizeof("/orgs/{org}"                         ) - 1, &route_data[112]);
        r3_tree_insert_routel(n, METHOD_GET,     "/orgs/{org}/members"                 , sizeof("/orgs/{org}/members"                 ) - 1, &route_data[113]);
        r3_tree_insert_routel(n, METHOD_GET,     "/orgs/{org}/members/{user}"          , sizeof("/orgs/{org}/members/{user}"          ) - 1, &route_data[114]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/orgs/{org}/members/{user}"          , sizeof("/orgs/{org}/members/{user}"          ) - 1, &route_data[115]);
        r3_tree_insert_routel(n, METHOD_GET,     "/orgs/{org}/public_members"          , sizeof("/orgs/{org}/public_members"          ) - 1, &route_data[116]);
        r3_tree_insert_routel(n, METHOD_GET,     "/orgs/{org}/public_members/{user}"   , sizeof("/orgs/{org}/public_members/{user}"   ) - 1, &route_data[117]);
        r3_tree_insert_routel(n, METHOD_PUT,     "/orgs/{org}/public_members/{user}"   , sizeof("/orgs/{org}/public_members/{user}"   ) - 1, &route_data[118]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/orgs/{org}/public_members/{user}"   , sizeof("/orgs/{org}/public_members/{user}"   ) - 1, &route_data[119]);
        r3_tree_insert_routel(n, METHOD_GET,     "/orgs/{org}/teams"                   , sizeof("/orgs/{org}/teams"                   ) - 1, &route_data[120]);
        r3_tree_insert_routel(n, METHOD_GET,     "/teams/{id}"                         , sizeof("/teams/{id}"                         ) - 1, &route_data[121]);
        r3_tree_insert_routel(n, METHOD_POST,    "/orgs/{org}/teams"                   , sizeof("/orgs/{org}/teams"                   ) - 1, &route_data[122]);
        r3_tree_insert_routel(n, METHOD_PATCH,   "/teams/{id}"                         , sizeof("/teams/{id}"                         ) - 1, &route_data[123]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/teams/{id}"                         , sizeof("/teams/{id}"                         ) - 1, &route_data[124]);
        r3_tree_insert_routel(n, METHOD_GET,     "/teams/{id}/members"                 , sizeof("/teams/{id}/members"                 ) - 1, &route_data[125]);
        r3_tree_insert_routel(n, METHOD_GET,     "/teams/{id}/members/{user}"          , sizeof("/teams/{id}/members/{user}"          ) - 1, &route_data[126]);
        r3_tree_insert_routel(n, METHOD_PUT,     "/teams/{id}/members/{user}"          , sizeof("/teams/{id}/members/{user}"          ) - 1, &route_data[127]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/teams/{id}/members/{user}"          , sizeof("/teams/{id}/members/{user}"          ) - 1, &route_data[128]);
        r3_tree_insert_routel(n, METHOD_GET,     "/teams/{id}/repos"                   , sizeof("/teams/{id}/repos"                   ) - 1, &route_data[129]);
        r3_tree_insert_routel(n, METHOD_GET,     "/teams/{id}/repos/{owner}/{repo}"    , sizeof("/teams/{id}/repos/{owner}/{repo}"    ) - 1, &route_data[130]);
        r3_tree_insert_routel(n, METHOD_PUT,     "/teams/{id}/repos/{owner}/{repo}"    , sizeof("/teams/{id}/repos/{owner}/{repo}"    ) - 1, &route_data[131]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/teams/{id}/repos/{owner}/{repo}"    , sizeof("/teams/{id}/repos/{owner}/{repo}"    ) - 1, &route_data[132]);
        r3_tree_insert_routel(n, METHOD_GET,     "/user/teams"                         , sizeof("/user/teams"                         ) - 1, &route_data[133]);


        // Pull Requests
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/pulls"                     , sizeof("/repos/{owner}/{repo}/pulls"                     ) - 1, &route_data[134]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/pulls/{number}"            , sizeof("/repos/{owner}/{repo}/pulls/{number}"            ) - 1, &route_data[135]);
        r3_tree_insert_routel(n, METHOD_POST,   "/repos/{owner}/{repo}/pulls"                     , sizeof("/repos/{owner}/{repo}/pulls"                     ) - 1, &route_data[136]);
        r3_tree_insert_routel(n, METHOD_PATCH,  "/repos/{owner}/{repo}/pulls/{number}"            , sizeof("/repos/{owner}/{repo}/pulls/{number}"            ) - 1, &route_data[137]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/pulls/{number}/commits"    , sizeof("/repos/{owner}/{repo}/pulls/{number}/commits"    ) - 1, &route_data[138]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/pulls/{number}/files"      , sizeof("/repos/{owner}/{repo}/pulls/{number}/files"      ) - 1, &route_data[139]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/pulls/{number}/merge"      , sizeof("/repos/{owner}/{repo}/pulls/{number}/merge"      ) - 1, &route_data[140]);
        r3_tree_insert_routel(n, METHOD_PUT,    "/repos/{owner}/{repo}/pulls/{number}/merge"      , sizeof("/repos/{owner}/{repo}/pulls/{number}/merge"      ) - 1, &route_data[141]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/pulls/{number}/comments"   , sizeof("/repos/{owner}/{repo}/pulls/{number}/comments"   ) - 1, &route_data[142]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/pulls/comments"            , sizeof("/repos/{owner}/{repo}/pulls/comments"            ) - 1, &route_data[143]);
        r3_tree_insert_routel(n, METHOD_GET,    "/repos/{owner}/{repo}/pulls/comments/{number}"   , sizeof("/repos/{owner}/{repo}/pulls/comments/{number}"   ) - 1, &route_data[144]);
        r3_tree_insert_routel(n, METHOD_PUT,    "/repos/{owner}/{repo}/pulls/{number}/comments"   , sizeof("/repos/{owner}/{repo}/pulls/{number}/comments"   ) - 1, &route_data[145]);
        r3_tree_insert_routel(n, METHOD_PATCH,  "/repos/{owner}/{repo}/pulls/comments/{number}"   , sizeof("/repos/{owner}/{repo}/pulls/comments/{number}"   ) - 1, &route_data[146]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/repos/{owner}/{repo}/pulls/comments/{number}"   , sizeof("/repos/{owner}/{repo}/pulls/comments/{number}"   ) - 1, &route_data[147]);


        // Repositories
        r3_tree_insert_routel(n, METHOD_GET,     "/user/repos"                                  , sizeof("/user/repos"                                  ) - 1, &route_data[148]);
        r3_tree_insert_routel(n, METHOD_GET,     "/users/{user}/repos"                          , sizeof("/users/{user}/repos"                          ) - 1, &route_data[149]);
        r3_tree_insert_routel(n, METHOD_GET,     "/orgs/{org}/repos"                            , sizeof("/orgs/{org}/repos"                            ) - 1, &route_data[150]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repositories"                                , sizeof("/repositories"                                ) - 1, &route_data[151]);
        r3_tree_insert_routel(n, METHOD_POST,    "/user/repos"                                  , sizeof("/user/repos"                                  ) - 1, &route_data[152]);
        r3_tree_insert_routel(n, METHOD_POST,    "/orgs/{org}/repos"                            , sizeof("/orgs/{org}/repos"                            ) - 1, &route_data[153]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}"                        , sizeof("/repos/{owner}/{repo}"                        ) - 1, &route_data[154]);
        r3_tree_insert_routel(n, METHOD_PATCH,   "/repos/{owner}/{repo}"                        , sizeof("/repos/{owner}/{repo}"                        ) - 1, &route_data[155]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/contributors"           , sizeof("/repos/{owner}/{repo}/contributors"           ) - 1, &route_data[156]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/languages"              , sizeof("/repos/{owner}/{repo}/languages"              ) - 1, &route_data[157]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/teams"                  , sizeof("/repos/{owner}/{repo}/teams"                  ) - 1, &route_data[158]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/tags"                   , sizeof("/repos/{owner}/{repo}/tags"                   ) - 1, &route_data[159]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/branches"               , sizeof("/repos/{owner}/{repo}/branches"               ) - 1, &route_data[160]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/branches/{branch}"      , sizeof("/repos/{owner}/{repo}/branches/{branch}"      ) - 1, &route_data[161]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/repos/{owner}/{repo}"                        , sizeof("/repos/{owner}/{repo}"                        ) - 1, &route_data[162]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/collaborators"          , sizeof("/repos/{owner}/{repo}/collaborators"          ) - 1, &route_data[163]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/collaborators/{user}"   , sizeof("/repos/{owner}/{repo}/collaborators/{user}"   ) - 1, &route_data[164]);
        r3_tree_insert_routel(n, METHOD_PUT,     "/repos/{owner}/{repo}/collaborators/{user}"   , sizeof("/repos/{owner}/{repo}/collaborators/{user}"   ) - 1, &route_data[165]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/repos/{owner}/{repo}/collaborators/{user}"   , sizeof("/repos/{owner}/{repo}/collaborators/{user}"   ) - 1, &route_data[166]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/comments"               , sizeof("/repos/{owner}/{repo}/comments"               ) - 1, &route_data[167]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/commits/{sha}/comments" , sizeof("/repos/{owner}/{repo}/commits/{sha}/comments" ) - 1, &route_data[168]);
        r3_tree_insert_routel(n, METHOD_POST,    "/repos/{owner}/{repo}/commits/{sha}/comments" , sizeof("/repos/{owner}/{repo}/commits/{sha}/comments" ) - 1, &route_data[169]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/comments/{id}"          , sizeof("/repos/{owner}/{repo}/comments/{id}"          ) - 1, &route_data[170]);
        r3_tree_insert_routel(n, METHOD_PATCH,   "/repos/{owner}/{repo}/comments/{id}"          , sizeof("/repos/{owner}/{repo}/comments/{id}"          ) - 1, &route_data[171]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/repos/{owner}/{repo}/comments/{id}"          , sizeof("/repos/{owner}/{repo}/comments/{id}"          ) - 1, &route_data[172]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/commits"                , sizeof("/repos/{owner}/{repo}/commits"                ) - 1, &route_data[173]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/commits/{sha}"          , sizeof("/repos/{owner}/{repo}/commits/{sha}"          ) - 1, &route_data[174]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/readme"                 , sizeof("/repos/{owner}/{repo}/readme"                 ) - 1, &route_data[175]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/contents/"              , sizeof("/repos/{owner}/{repo}/contents/"              ) - 1, &route_data[176]);
        r3_tree_insert_routel(n, METHOD_PUT,     "/repos/{owner}/{repo}/contents/"              , sizeof("/repos/{owner}/{repo}/contents/"              ) - 1, &route_data[177]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/repos/{owner}/{repo}/contents/"              , sizeof("/repos/{owner}/{repo}/contents/"              ) - 1, &route_data[178]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/{archive_format}/{ref}" , sizeof("/repos/{owner}/{repo}/{archive_format}/{ref}" ) - 1, &route_data[179]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/keys"                   , sizeof("/repos/{owner}/{repo}/keys"                   ) - 1, &route_data[180]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/keys/{id}"              , sizeof("/repos/{owner}/{repo}/keys/{id}"              ) - 1, &route_data[181]);
        r3_tree_insert_routel(n, METHOD_POST,    "/repos/{owner}/{repo}/keys"                   , sizeof("/repos/{owner}/{repo}/keys"                   ) - 1, &route_data[182]);
        r3_tree_insert_routel(n, METHOD_PATCH,   "/repos/{owner}/{repo}/keys/{id}"              , sizeof("/repos/{owner}/{repo}/keys/{id}"              ) - 1, &route_data[183]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/repos/{owner}/{repo}/keys/{id}"              , sizeof("/repos/{owner}/{repo}/keys/{id}"              ) - 1, &route_data[184]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/downloads"              , sizeof("/repos/{owner}/{repo}/downloads"              ) - 1, &route_data[185]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/downloads/{id}"         , sizeof("/repos/{owner}/{repo}/downloads/{id}"         ) - 1, &route_data[186]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/repos/{owner}/{repo}/downloads/{id}"         , sizeof("/repos/{owner}/{repo}/downloads/{id}"         ) - 1, &route_data[187]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/forks"                  , sizeof("/repos/{owner}/{repo}/forks"                  ) - 1, &route_data[188]);
        r3_tree_insert_routel(n, METHOD_POST,    "/repos/{owner}/{repo}/forks"                  , sizeof("/repos/{owner}/{repo}/forks"                  ) - 1, &route_data[189]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/hooks"                  , sizeof("/repos/{owner}/{repo}/hooks"                  ) - 1, &route_data[190]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/hooks/{id}"             , sizeof("/repos/{owner}/{repo}/hooks/{id}"             ) - 1, &route_data[191]);
        r3_tree_insert_routel(n, METHOD_POST,    "/repos/{owner}/{repo}/hooks"                  , sizeof("/repos/{owner}/{repo}/hooks"                  ) - 1, &route_data[192]);
        r3_tree_insert_routel(n, METHOD_PATCH,   "/repos/{owner}/{repo}/hooks/{id}"             , sizeof("/repos/{owner}/{repo}/hooks/{id}"             ) - 1, &route_data[193]);
        r3_tree_insert_routel(n, METHOD_POST,    "/repos/{owner}/{repo}/hooks/{id}/tests"       , sizeof("/repos/{owner}/{repo}/hooks/{id}/tests"       ) - 1, &route_data[194]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/repos/{owner}/{repo}/hooks/{id}"             , sizeof("/repos/{owner}/{repo}/hooks/{id}"             ) - 1, &route_data[195]);
        r3_tree_insert_routel(n, METHOD_POST,    "/repos/{owner}/{repo}/merges"                 , sizeof("/repos/{owner}/{repo}/merges"                 ) - 1, &route_data[196]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/releases"               , sizeof("/repos/{owner}/{repo}/releases"               ) - 1, &route_data[197]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/releases/{id}"          , sizeof("/repos/{owner}/{repo}/releases/{id}"          ) - 1, &route_data[198]);
        r3_tree_insert_routel(n, METHOD_POST,    "/repos/{owner}/{repo}/releases"               , sizeof("/repos/{owner}/{repo}/releases"               ) - 1, &route_data[199]);
        r3_tree_insert_routel(n, METHOD_PATCH,   "/repos/{owner}/{repo}/releases/{id}"          , sizeof("/repos/{owner}/{repo}/releases/{id}"          ) - 1, &route_data[200]);
        r3_tree_insert_routel(n, METHOD_DELETE,  "/repos/{owner}/{repo}/releases/{id}"          , sizeof("/repos/{owner}/{repo}/releases/{id}"          ) - 1, &route_data[201]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/releases/{id}/assets"   , sizeof("/repos/{owner}/{repo}/releases/{id}/assets"   ) - 1, &route_data[202]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/stats/contributors"     , sizeof("/repos/{owner}/{repo}/stats/contributors"     ) - 1, &route_data[203]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/stats/commit_activity"  , sizeof("/repos/{owner}/{repo}/stats/commit_activity"  ) - 1, &route_data[204]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/stats/code_frequency"   , sizeof("/repos/{owner}/{repo}/stats/code_frequency"   ) - 1, &route_data[205]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/stats/participation"    , sizeof("/repos/{owner}/{repo}/stats/participation"    ) - 1, &route_data[206]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/stats/punch_card"       , sizeof("/repos/{owner}/{repo}/stats/punch_card"       ) - 1, &route_data[207]);
        r3_tree_insert_routel(n, METHOD_GET,     "/repos/{owner}/{repo}/statuses/{ref}"         , sizeof("/repos/{owner}/{repo}/statuses/{ref}"         ) - 1, &route_data[208]);
        r3_tree_insert_routel(n, METHOD_POST,    "/repos/{owner}/{repo}/statuses/{ref}"         , sizeof("/repos/{owner}/{repo}/statuses/{ref}"         ) - 1, &route_data[209]);

        // Search
        r3_tree_insert_routel(n, METHOD_GET,    "/search/repositories"                                        , sizeof("/search/repositories"                                        ) - 1, &route_data[210]);
        r3_tree_insert_routel(n, METHOD_GET,    "/search/code"                                                , sizeof("/search/code"                                                ) - 1, &route_data[211]);
        r3_tree_insert_routel(n, METHOD_GET,    "/search/issues"                                              , sizeof("/search/issues"                                              ) - 1, &route_data[212]);
        r3_tree_insert_routel(n, METHOD_GET,    "/search/users"                                               , sizeof("/search/users"                                               ) - 1, &route_data[213]);
        r3_tree_insert_routel(n, METHOD_GET,    "/legacy/issues/search/{owner}/{repository}/{state}/{keyword}", sizeof("/legacy/issues/search/{owner}/{repository}/{state}/{keyword}") - 1, &route_data[214]);
        r3_tree_insert_routel(n, METHOD_GET,    "/legacy/repos/search/{keyword"                               , sizeof("/legacy/repos/search/{keyword"                               ) - 1, &route_data[215]);
        r3_tree_insert_routel(n, METHOD_GET,    "/legacy/user/search/{keyword}"                               , sizeof("/legacy/user/search/{keyword}"                               ) - 1, &route_data[216]);
        r3_tree_insert_routel(n, METHOD_GET,    "/legacy/user/email/{email}"                                  , sizeof("/legacy/user/email/{email}"                                  ) - 1, &route_data[217]);


        // Users
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}"                           , sizeof("/users/{user}"                           ) - 1, &route_data[218]);
        r3_tree_insert_routel(n, METHOD_GET,    "/user"                                   , sizeof("/user"                                   ) - 1, &route_data[219]);
        r3_tree_insert_routel(n, METHOD_PATCH,  "/user"                                   , sizeof("/user"                                   ) - 1, &route_data[220]);
        r3_tree_insert_routel(n, METHOD_GET,    "/users"                                  , sizeof("/users"                                  ) - 1, &route_data[221]);
        r3_tree_insert_routel(n, METHOD_GET,    "/user/emails"                            , sizeof("/user/emails"                            ) - 1, &route_data[222]);
        r3_tree_insert_routel(n, METHOD_POST,   "/user/emails"                            , sizeof("/user/emails"                            ) - 1, &route_data[223]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/user/emails"                            , sizeof("/user/emails"                            ) - 1, &route_data[224]);
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}/followers"                 , sizeof("/users/{user}/followers"                 ) - 1, &route_data[225]);
        r3_tree_insert_routel(n, METHOD_GET,    "/user/followers"                         , sizeof("/user/followers"                         ) - 1, &route_data[226]);
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}/following"                 , sizeof("/users/{user}/following"                 ) - 1, &route_data[227]);
        r3_tree_insert_routel(n, METHOD_GET,    "/user/following"                         , sizeof("/user/following"                         ) - 1, &route_data[228]);
        r3_tree_insert_routel(n, METHOD_GET,    "/user/following/{user}"                  , sizeof("/user/following/{user}"                  ) - 1, &route_data[229]);
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}/following/{target_user}"   , sizeof("/users/{user}/following/{target_user}"   ) - 1, &route_data[230]);
        r3_tree_insert_routel(n, METHOD_PUT,    "/user/following/{user}"                  , sizeof("/user/following/{user}"                  ) - 1, &route_data[230]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/user/following/{user}"                  , sizeof("/user/following/{user}"                  ) - 1, &route_data[231]);
        r3_tree_insert_routel(n, METHOD_GET,    "/users/{user}/keys"                      , sizeof("/users/{user}/keys"                      ) - 1, &route_data[232]);
        r3_tree_insert_routel(n, METHOD_GET,    "/user/keys"                              , sizeof("/user/keys"                              ) - 1, &route_data[233]);
        r3_tree_insert_routel(n, METHOD_GET,    "/user/keys/{id}"                         , sizeof("/user/keys/{id}"                         ) - 1, &route_data[234]);
        r3_tree_insert_routel(n, METHOD_POST,   "/user/keys"                              , sizeof("/user/keys"                              ) - 1, &route_data[235]);
        r3_tree_insert_routel(n, METHOD_PATCH,  "/user/keys/{id}"                         , sizeof("/user/keys/{id}"                         ) - 1, &route_data[236]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/user/keys/{id}"                         , sizeof("/user/keys/{id}"                         ) - 1, &route_data[237]);


        char *errstr = NULL;
        int err = r3_tree_compile(n, &errstr);
        if(errstr != nullptr)
        {
            std::cout << "err = " << errstr;
        }
    }

    void TearDown(const ::benchmark::State& state) BENCHMARK_OVERRIDE
    {
        r3_tree_free(n);
        n = nullptr;
    }

    void Execute(::benchmark::State& state)
    {
        for (auto _ : state)
        {
            Execute();
        }
    }

    void CallRoute(int method, const char* path)
    {
        match_entry * entry = match_entry_create(path);
        entry->request_method = method;

        auto* matched_R3Route = r3_tree_match_route(n, entry);
        match_entry_free(entry);


    }

    void Execute()
    {
        CallRoute(METHOD_GET,       "/user/keys");
        CallRoute(METHOD_POST,      "/user/keys");
        CallRoute(METHOD_PUT,       "/user/following/486546843546546546");
        CallRoute(METHOD_GET,       "/legacy/issues/search/565435413654651651/65435146516351654/54684351351/1568463516");
        CallRoute(METHOD_GET,       "/repos/65435143513514/6543513543513/releases/165435135416541");
        CallRoute(METHOD_GET,       "/repos/6543543541354654/6543531546565/contents/a/big/content");
        CallRoute(METHOD_GET,       "/repositories");
        CallRoute(METHOD_DELETE,    "/repos/15654354654654/165435135416543/pulls/comments/1654351435413513");
        CallRoute(METHOD_GET,       "/teams/65465454654654/repos/4654354354654/465413516541321");
        CallRoute(METHOD_PUT,       "/teams/65465454654654/repos/56465465146/456543513546546641541");


        CallRoute(METHOD_GET,       "/users/146545136561645451/orgs");
        CallRoute(METHOD_GET,       "/gists");
        CallRoute(METHOD_GET,       "/markdown");
        CallRoute(METHOD_GET,       "/repos/163545435435/46543516546545/issues/comments/156543546546514");
        CallRoute(METHOD_GET,       "/repos/1654351351543/135435135135/issues/354365413513514/comments");
        CallRoute(METHOD_DELETE,    "/authorizations/1354654151545");
        CallRoute(METHOD_GET,       "/applications/841165616164161616/tokens/1654654516565");
        CallRoute(METHOD_GET,       "/user/keys");
        CallRoute(METHOD_GET,       "/legacy/user/email/15654564");
        CallRoute(METHOD_GET,       "/not/found");
    }
};

BENCHMARK_F(Github_R3Benchmark, R3)(benchmark::State& st)
{
    Execute(st);
}

#endif

#endif