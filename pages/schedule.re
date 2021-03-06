open Util;

module Link = ReactRouterDom.Link;

[@bs.module] external style: Js.t({..}) = "./schedule.module.scss";

let talkSlug = Data.Speaker.talkSlug;

let component = ReasonReact.statelessComponent("Schedule");

let toTimeStr = (~fromTime, ~toTime) =>
  switch (toTime) {
  | Some(toTime) => toHHMM(fromTime) ++ {j|–|j} ++ toHHMM(toTime)
  | None => toHHMM(fromTime) ++ {j|–∞|j}
  };

let toDayStr = (~date) => {
  let format = "YYYY-MM-DDTHH:mm:ss.SSSZ";
  DateFns.format(format, date);
};
let toDurationStr = (~fromTime, ~toTime) => {
  let format = "YYYY-MM-DDTHH:mm:ss.SSSZ";
  switch (toTime) {
  | Some(toTime) =>
    DateFns.format(format, fromTime) ++ "/" ++ DateFns.format(format, toTime)
  | None => DateFns.format(format, fromTime)
  };
};

let miscRow = (~fromTime, ~toTime, description) =>
  ReasonReact.array([|
    <dt className=style##entryTime>
      <time dateTime={toDurationStr(~fromTime, ~toTime)}>
        {toTimeStr(~fromTime, ~toTime) |> s}
      </time>
    </dt>,
    <dd className=style##entryDescription> {description |> s} </dd>,
  |]);

/*
 A Break and a Misc type are structurally the same (for now).
 For semantic reasons, we still keep a different function
 name, in case we need to write a different render impl
 */
let breakRow = miscRow;

let talkRow = (~fromTime, ~toTime, speaker: Data.Speaker.t) =>
  ReasonReact.array([|
    <dt className=style##talkTime>
      <time dateTime={toDurationStr(~fromTime, ~toTime)}>
        {toTimeStr(~fromTime, ~toTime) |> s}
      </time>
    </dt>,
    <dd className=style##talkDescription>
      {
        switch (speaker.talk) {
        | Some(talk) =>
          let id = Data.Speaker.talkSlug(talk);
          <section className=style##talkDetails id>
            <h3 className=style##talkTitle>
              {talk.title |> s}
              {" " |> s}
              <a href={"#" ++ id} title={talk.title}> {"#" |> s} </a>
            </h3>
            <Link to_={"/speakers/#" ++ Data.Speaker.speakerAnchor(speaker)}>
              <SpeakerCard speaker compact=true />
            </Link>
            {talk.abstract |> md}
          </section>;
        | None => ReasonReact.null
        }
      }
    </dd>,
  |]);

let workshopRow = (~fromTime, ~toTime, speakers: list(Data.Speaker.t)) => {
  let renderSpeaker = speaker =>
    <Link to_={"/speakers/#" ++ Data.Speaker.speakerAnchor(speaker)}>
      <SpeakerCard speaker compact=true />
    </Link>;
  ReasonReact.array([|
    <dt className=style##talkTime>
      <time dateTime={toDurationStr(~fromTime, ~toTime)}>
        {toTimeStr(~fromTime, ~toTime) |> s}
      </time>
    </dt>,
    <dd className=style##talkDescription>
      <section className=style##talkDetails>
        <h3 className=style##talkTitle> {"Workshop" |> s} </h3>
        <p>
          {
            "An optional workshop to make every beginner and intermediate attendee familiar with the language, the BuckleScript platform as well as ReasonReact."
            |> s
          }
        </p>
        {
          speakers
          |> List.map(renderSpeaker)
          |> Array.of_list
          |> ReasonReact.array
        }
      </section>
    </dd>,
  |]);
};

let openEndRow = (~fromTime, ~toTime, description) =>
  ReasonReact.array([|
    <dt className=style##entryTime>
      <time dateTime={toDurationStr(~fromTime, ~toTime=None)}>
        {toTimeStr(~fromTime, ~toTime) |> s}
      </time>
    </dt>,
    <dd className=style##entryDescription> {description |> s} </dd>,
  |]);

let createRow = ({task, fromTime, toTime}: Data.Timetable.entry) =>
  switch (task) {
  | Break(description) => breakRow(~fromTime, ~toTime, description)
  | Misc(description) => miscRow(~fromTime, ~toTime, description)
  | Talk(speaker) => talkRow(~fromTime, ~toTime, speaker)
  | Workshop(speakers) => workshopRow(~fromTime, ~toTime, speakers)
  | OpenEnd(description) => openEndRow(~fromTime, description, ~toTime)
  };

let createDay = ({date, entries}: Data.Timetable.day) => {
  let id = DateFns.format("DD-MM-YY", date);
  <>
    <h2 id className="headingWithAnchor">
      <time dateTime={DateFns.format("YYYY-MM-DDTHH:mm:ss.SSSZ", date)}>
        {DateFns.format("Do MMMM, dddd", date) |> s}
      </time>
      <a href={"#" ++ id}> {"#" |> s} </a>
    </h2>
    <dl className=style##entries>
      {entries |> List.map(createRow) |> Array.of_list |> ReasonReact.array}
    </dl>
  </>;
};

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <h1> {"Schedule" |> s} </h1>
      {
        Data.Timetable.days
        |> List.map(createDay)
        |> Array.of_list
        |> ReasonReact.array
      }
    </div>,
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps => make(jsProps##children));
