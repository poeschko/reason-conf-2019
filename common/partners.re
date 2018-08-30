[@bs.module]
external agentLogo: string = "../assets/img/partners/agent-conf.svg";

[@bs.module]
external reactAmsterdamLogo: string =
  "../assets/img/partners/react-amsterdam.svg";

[@bs.module]
external reactFinlandLogo: string = "../assets/img/partners/react-finland.svg";

[@bs.module]
external reactViennaLogo: string = "../assets/img/partners/React-Vienna.svg";

[@bs.module]
external reasonviennaLogo: string = "../assets/img/partners/reasonvienna.svg";

[@bs.module]
external scriptConfLogo: string = "../assets/img/partners/script-conf.svg";

[@bs.module]
external impactHubLogo: string = "../assets/img/partners/impacthub-logo.png";

[@bs.module]
external accentureLogo: string = "../assets/img/partners/accenture-logo.svg";

[@bs.module]
external janeStreetLogo: string = "../assets/img/partners/janestreet-logo.svg";

[@bs.module] external g2iLogo: string = "../assets/img/partners/g2i-logo.svg";

[@bs.module]
external tuCCLogo: string = "../assets/img/partners/tucc-logo.svg";

type sponsorT = {
  name: string,
  logoUrl: string,
  href: string,
  tier: Data.Tier.tier,
};

let sponsors = [|
  {
    name: "Accenture",
    logoUrl: accentureLogo,
    href: "https://www.accenture.com",
    tier: Gold,
  },
  {
    name: "JaneStreet",
    logoUrl: janeStreetLogo,
    href: "https://www.janestreet.com",
    tier: Catering,
  },
  {name: "G2i", logoUrl: g2iLogo, href: "https://g2i.co", tier: LocalSupport},
|];

let partners = [|
  {
    name: "TU Career Center",
    logoUrl: tuCCLogo,
    href: "https://www.tucareer.com/",
    tier: Partner,
  },
  {
    name: "Impact Hub",
    logoUrl: impactHubLogo,
    href: "https://vienna.impacthub.net",
    tier: Partner,
  },
  {
    name: "Agent Conf",
    logoUrl: agentLogo,
    href: "https://www.agent.sh/",
    tier: Partner,
  },
  {
    name: "React Amsterdam",
    logoUrl: reactAmsterdamLogo,
    href: "https://react.amsterdam",
    tier: Partner,
  },
  {
    name: "React Finland",
    logoUrl: reactFinlandLogo,
    href: "https://react-finland.fi",
    tier: Partner,
  },
  {
    name: "React Vienna",
    logoUrl: reactViennaLogo,
    href: "https://www.meetup.com/ReactVienna/",
    tier: Partner,
  },
  {
    name: "ReasonVienna",
    logoUrl: reasonviennaLogo,
    href: "https://www.meetup.com/Reason-Vienna/",
    tier: Partner,
  },
  {
    name: "Script Conf",
    logoUrl: scriptConfLogo,
    href: "https://scriptconf.org",
    tier: Partner,
  },
|];
