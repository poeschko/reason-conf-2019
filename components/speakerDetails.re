open Util;

[@bs.module] external style: Js.t({..}) = "./speakerDetails.module.scss";

module Link = ReactRouterDom.Link;

let talkSlug = Data.Speaker.talkSlug;

let component = ReasonReact.statelessComponent("SpeakerDetails");

let make = (~speaker: Data.Speaker.t, _children) => {
  ...component,
  render: _self =>
    <section className=style##root id={Data.Speaker.speakerAnchor(speaker)}>
      <section className=style##speakerCard> <SpeakerCard speaker /> </section>
      <section className=style##description>
        <h2 className=style##name> {speaker.name |> s} </h2>
        <p className=style##company>
          {speaker.company ++ ", " |> s}
          <div className=style##social>
            <SocialLink target=Twitter link={speaker.social.twitterUser} />
            <SocialLink target=Github link={speaker.social.githubUser} />
            <SocialLink target=Website link={speaker.social.website} />
          </div>
        </p>
        {speaker.description |> md}
        {
          switch (speaker.talk) {
          | Some(t) =>
            <strong>
              {{j|🗣|j} |> s}
              <Link to_={"/schedule/#" ++ talkSlug(t)}> {t.title |> s} </Link>
            </strong>
          | None => ReasonReact.null
          }
        }
      </section>
    </section>,
};
